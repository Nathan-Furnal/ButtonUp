#include "view.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>

View::View(QWidget *parent) : QWidget{parent} {
  layout = new QGridLayout;
  setLayout(layout);
  m_table = new TableView;
  // make table fill available space and evenly stretch rows/columns
  m_table->horizontalHeader()->setStretchLastSection(true);
  m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_table->verticalHeader()->setStretchLastSection(true);
  m_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  // show useful data and set items within layout
  redVictoryPoints = new QLCDNumber(2);
  blackVictoryPoints = new QLCDNumber(2);
  turns = new QLCDNumber(1);
  turns->setMaximumHeight(35);
  layout->addWidget(
      m_table, 0, 0, 9,
      9); // 9 x 9 grid because there are 9 buttons per stack and 9 stacks
  layout->addWidget(createLabel(tr("TURNS")), 10, 0);
  layout->addWidget(turns, 10, 1);
  layout->addWidget(createLabel(tr("RED VICTORY POINTS")), 10, 3);
  layout->addWidget(redVictoryPoints, 10, 4);
  layout->addWidget(createLabel(tr("BLACK VICTORY POINTS")), 10, 6);
  layout->addWidget(blackVictoryPoints, 10, 7);
  layout->addWidget(createLabel(tr("GAME STATE")), 0, 10);
  layout->addWidget(gameState, 1, 10);
  gameState->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
  // --- Add the model ---//
  m_model = new QtModel;
  m_model->setParent(this); // ensures model cleanup when View is destroyed
  m_table->setModel(m_model);
  connectToModel();
  // --- Aesthetic --- //
  this->setMinimumSize(1380, 500);
  this->setWindowTitle("ButtonUp!");
  this->show();
  // Ask for first player on startup
  pickFirstPlayer();
}

void View::connectToModel() {
  // Connects the signaler and its signal to the receiver and its slot (reaction to signal)
  QTableView::connect(m_table, SIGNAL(clicked(QModelIndex)),
                      m_table->model(),
                      SLOT(moveStacksOnColumnClicked(QModelIndex)));
  connect(m_model, &QtModel::turnChanged, turns,
          qOverload<int>(&QLCDNumber::display));
  connect(m_model, &QtModel::stateChanged, this, &View::setGameState);
  connect(m_model, &QtModel::redTally, redVictoryPoints,
          qOverload<int>(&QLCDNumber::display));
  connect(m_model, &QtModel::blackTally, blackVictoryPoints,
          qOverload<int>(&QLCDNumber::display));
  connect(m_model, &QtModel::roundTally, this, &View::tally);
  connect(this, &View::replay, m_model, &QtModel::replay);
  connect(m_model, &QtModel::endGame, this, &View::endGame);
}

void View::pickFirstPlayer() {
  QMessageBox msgBox;
  msgBox.setWindowTitle("First player pick 🕹️");
  msgBox.setModal(true);
  msgBox.setText("Pick the player who goes first!");
  QPushButton *buttonRed = msgBox.addButton(tr("Red"), QMessageBox::YesRole);

  QPushButton *buttonBlack = msgBox.addButton(tr("Black"), QMessageBox::NoRole);
  msgBox.setDefaultButton(buttonRed);
  msgBox.exec();
  if (msgBox.clickedButton() == buttonRed) {
    m_model->setState(Game::GameState::RED);
  } else if (msgBox.clickedButton() == buttonBlack) {
    m_model->setState(Game::GameState::BLACK);
  }
}

QLabel *View::createLabel(const QString &str) {
  QLabel *label = new QLabel(str);
  label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
  return label;
}

void View::setGameState(Game::GameState gs) {
  switch (gs) {
  case Game::GameState::BEGIN:
    gameState->setText("Pick a player!");
    break;
  case Game::GameState::RED:
    gameState->setText("Red's turn!");
    break;
  case Game::GameState::BLACK:
    gameState->setText("Black's turn!");
    break;
  case Game::GameState::GAME_OVER:
    gameState->setText("Game over!");
    break;
  }
}

void View::tally(int redRes, int blackRes) {
  QMessageBox msgBox;
  msgBox.setWindowTitle("Round ended!");
  std::string winner;
  if (redRes > blackRes) {
    winner = "RED";
  } else if (redRes < blackRes) {
    winner = "BLACK";
  } else {
    winner = "No one";
  }
  int out = abs(redRes - blackRes);
  QString msg = tr("%1 won!\n").arg(winner.c_str());
  QString content =
      tr("RED got %1 points.\nBLACK got %2 points.\nThe player with "
         "the larger amount of points gets the difference in "
         "victory points (%3 points).\n\nWould you like to play again?")
          .arg(QString::number(redRes), QString::number(blackRes),
               QString::number(out));
  msg.append(content);
  msgBox.setText(msg);
  msgBox.addButton(QMessageBox::Yes);
  msgBox.addButton(QMessageBox::No);
  msgBox.exec();
  if (msgBox.result() == QMessageBox::Yes) {
    emit replay();
    pickFirstPlayer();
  } else {
    this->close();
  }
}

void View::endGame(int redRes, int blackRes){
   QMessageBox msgBox;
  msgBox.setWindowTitle("Game ended! 🏆");
  std::string winner = (redRes > blackRes) ? "RED" : "BLACK";
  QString msg = tr("The winner is %1 ⭐⭐⭐\n\nThanks for playing!").arg(winner.c_str());
  msgBox.setText(msg);
  QPushButton* btn = msgBox.addButton(tr("Bye!"), QMessageBox::YesRole);
  msgBox.exec();
  // The illusion of choice
  if(msgBox.clickedButton() == btn){
      this->close();
  }
  else{
      this->close();
  }
}
