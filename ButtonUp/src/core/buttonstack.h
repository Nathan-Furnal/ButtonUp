#ifndef BUTTONSTACK_H
#define BUTTONSTACK_H
#include "button.h"
#include <array>

class ButtonStack {
public:
  ButtonStack();
  static const int N_BUTTONS = 9;
  bool hasWhite();
  bool isEmpty();
  int nButtons();
  void push(enum Button b);
  void reset();
  bool has2SameButtons();
  enum Button operator[](int idx);

private:
  int m_stackPointer = 0;
  std::array<Button, 9> m_stack;
};

#endif // BUTTONSTACK_H
