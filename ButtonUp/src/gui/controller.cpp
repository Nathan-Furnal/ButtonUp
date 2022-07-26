#include "controller.h"

Controller::Controller(QtModel &model, View &view, Game &game, MainWindow &w)
    : m_model(model), m_view(view), m_game(game), m_window(w) {
  model.setGame(&game);
  view.setModel(&model);
  QTableView::connect(&view, SIGNAL(clicked(const QModelIndex &)), &model,
                      SLOT(moveStacksOnColumnClicked(const QModelIndex &)));
  m_window.setCentralWidget(&view);
}

void Controller::start() {
  m_window.setMinimumSize(1250, 500);
  m_window.setWindowTitle("ButtonUp!");
  m_window.show();
}
