#include "qtmodel.h"

#include <QBrush>
#include <QMessageBox>
#include <QModelIndex>

QtModel::QtModel(QObject *parent) : QAbstractTableModel(parent) {
    m_game = new Game;
}

// See https://doc.qt.io/qt-6/modelview.html#2-1-a-read-only-table

QVariant QtModel::headerData(int section, Qt::Orientation orientation,
                             int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
    for (int i = 0; i < ButtonStack::N_BUTTONS; i++) {
      const std::string rowHeader = std::to_string(ButtonStack::N_BUTTONS - i);
      if (i == section) {
        return QString(rowHeader.c_str());
      }
    }
  }
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    for (int i = 0; i < ButtonStack::N_BUTTONS; i++) {
      const std::string colHeader = std::to_string(i + 1);
      if (i == section) {
        return QString(colHeader.c_str());
      }
    }
  }
  return QVariant();
}

int QtModel::rowCount(const QModelIndex & /*parent*/) const { return ButtonStack::N_BUTTONS; }

int QtModel::columnCount(const QModelIndex & /*parent*/) const { return Game::N_STACKS; }

QVariant QtModel::data(const QModelIndex &index, int role) const {
  int row = index.row();
  int col = index.column();
  if (role == Qt::BackgroundRole) {
    Button dat = (*m_game)[col][ButtonStack::N_BUTTONS - row - 1];
    switch (dat) {
    case Button::EMPTY:
      return QBrush(QColorConstants::Svg::lightgray);
    case Button::RED:
      return QBrush(QColorConstants::Svg::orangered);
    case Button::BLACK:
      return QBrush(QColorConstants::Svg::black);
    case Button::WHITE:
      return QBrush(QColorConstants::Svg::ghostwhite);
    }
  }
  if (role == Qt::ToolTipRole) {
    Button dat = (*m_game)[col][ButtonStack::N_BUTTONS - row - 1];
    switch (dat) {
    case Button::EMPTY:
      return QString("Empty button");
    case Button::RED:
      return QString("Red button");
    case Button::BLACK:
      return QString("Black button");
    case Button::WHITE:
      return QString("White button");
    }
  }

  return QVariant();
}

void QtModel::moveStacksOnColumnClicked(const QModelIndex &idx) {
  if (idx.isValid()) {
    if ((*m_game)[idx.column()].hasWhite()) {
      m_game->moveStack(idx.column());
      emit dataChanged(index(0, 0),
                       index(ButtonStack::N_BUTTONS, m_game->N_STACKS));
      emit turnChanged(m_game->turns());
      emit stateChanged(m_game->getState());
      if (m_game->isGameOver()) {
        m_game->computeRoundPoints();
        emit redTally(m_game->redVictoryPoints());
        emit blackTally(m_game->blackVictoryPoints());
        if ((m_game->redVictoryPoints() >= 15 &&
             m_game->redVictoryPoints() > m_game->blackVictoryPoints()) ||
            (m_game->blackVictoryPoints() >= 15 &&
             m_game->blackVictoryPoints() > m_game->redVictoryPoints())) {
          emit endGame(m_game->redVictoryPoints(),
                       m_game->blackVictoryPoints());
        } else {
          emit roundTally(m_game->redRoundResult(), m_game->blackRoundResult());
        }
      }
    } else {
      QMessageBox msgBox;
      msgBox.setWindowTitle("Rule notification 🎮");
      msgBox.setText("Only stacks with white buttons can be moved.");
      msgBox.exec();
    }
  }
}

void QtModel::setState(Game::GameState gs){
  m_game->setState(gs);
  emit stateChanged(m_game->getState());
}

void QtModel::replay() {
  m_game->reset();
  emit turnChanged(m_game->turns());
  emit stateChanged(m_game->getState());
  m_game->shuffleStacks();
  emit dataChanged(index(0, 0),
                   index(ButtonStack::N_BUTTONS, m_game->N_STACKS));
}

QtModel::~QtModel(){
    delete m_game;
}
