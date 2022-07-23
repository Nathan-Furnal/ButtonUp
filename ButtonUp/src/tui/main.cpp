#include "controller.h"

int main(void) {
  Game g{};
  View v{g};
  Controller c{g, v};
  c.start();
  return 0;
}
