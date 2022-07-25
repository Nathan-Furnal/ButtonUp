#include "mainwindow.h"
#include "qtmodel.h"
#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow window;
  QTableView tableView;
  Game *gamePointer{new Game};
  QtModel model;
  model.setGame(gamePointer);
  tableView.setModel(&model);
  window.setCentralWidget(&tableView);
  window.resize(1400, 600);
  window.setWindowTitle("ButtonUp!");
  window.show();
  int ret = app.exec();
  delete gamePointer;
  return ret;
}
