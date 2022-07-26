#include "controller.h"
#include "mainwindow.h"
#include "qtmodel.h"
#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow window;
  View tableView;
  Game game{};
  QtModel model;
  Controller controller{model, tableView, game, window};
  controller.start();
  int ret = app.exec();
  return ret;
}
