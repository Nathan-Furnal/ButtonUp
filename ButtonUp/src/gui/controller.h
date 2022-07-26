#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "qtmodel.h"
#include "view.h"
#include <QTableView>

class Controller {
public:
  Controller(QtModel &model, View &view, Game &game, MainWindow &w);
  void start();

private:
  QtModel &m_model;
  View &m_view;
  Game &m_game;
  QMainWindow &m_window;
};

#endif // CONTROLLER_H
