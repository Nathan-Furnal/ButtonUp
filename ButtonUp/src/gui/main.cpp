#include "view.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
    View view{};
  return app.exec();
}
