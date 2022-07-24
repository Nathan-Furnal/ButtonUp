#include "buttonstack.h"
#include "button.h"

ButtonStack::ButtonStack() { m_stack.fill(Button::EMPTY); }
bool ButtonStack::isEmpty() { return m_stack[0] == Button::EMPTY; }

bool ButtonStack::hasWhite() {
  for (auto const &el : m_stack) {
    if (el == Button::WHITE)
      return true;
  }
  return false;
}

int ButtonStack::nButtons() { return m_stackPointer; }

void ButtonStack::push(enum Button b) {
  if (b != Button::EMPTY && m_stackPointer <= N_BUTTONS) {
    m_stack[m_stackPointer++] = b;
  }
}

Button ButtonStack::pop() {
  if (!isEmpty()) {
    Button b = m_stack[--m_stackPointer];
    m_stack[m_stackPointer] = Button::EMPTY;
    return b;
  } else {
    return Button::EMPTY;
  }
}

void ButtonStack::reset() {
  m_stackPointer = 0;
  std::fill(m_stack.begin(), m_stack.end(), Button::EMPTY);
}

void ButtonStack::stackOnto(ButtonStack &otherStack) {
  int i = 0;
  Button b = m_stack[i];
  while (b != Button::EMPTY) {
    otherStack.push(b);
    b = m_stack[++i];
  }
  reset();
}

enum Button ButtonStack::operator[](int idx) { return m_stack.at(idx); }

bool ButtonStack::has2SameButtons() {
  if (nButtons() < 2) {
    return false;
  } else {
    return m_stack[m_stackPointer - 1] == m_stack[m_stackPointer - 2];
  }
}
