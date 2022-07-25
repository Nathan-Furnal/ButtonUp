#include "buttonstack.h"
#include "button.h"

ButtonStack::ButtonStack() { m_stack.fill(Button::EMPTY); }
bool ButtonStack::isEmpty() const { return m_stack[0] == Button::EMPTY; }

bool ButtonStack::hasWhite() const {
  for (auto const &el : m_stack) {
    if (el == Button::WHITE)
      return true;
  }
  return false;
}

int ButtonStack::nButtons() const { return m_stackPointer; }

void ButtonStack::push(enum Button b) {
  if (b != Button::EMPTY && m_stackPointer <= N_BUTTONS) {
    m_stack[m_stackPointer++] = b;
  }
}

void ButtonStack::reset() {
  m_stackPointer = 0;
  std::fill(m_stack.begin(), m_stack.end(), Button::EMPTY);
}

enum Button ButtonStack::operator[](int idx) { return m_stack.at(idx); }

bool ButtonStack::has2SameButtons() {
  if (nButtons() < 2) {
    return false;
  } else {
    return m_stack[m_stackPointer - 1] == m_stack[m_stackPointer - 2];
  }
}
