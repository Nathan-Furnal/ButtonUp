#ifndef BUTTONSTACK_H
#define BUTTONSTACK_H
#include "button.h"
#include <array>
/**
 * @brief The ButtonStack class which implements the logic of a 1-9 buttons
 * stack in the game. It works as a somewhat hybrid datastructure, it behaves
 * like a proper stack to add new elements but supports 0(1) random access like
 * an array. Removed elements are not popped but iterated over, like an array
 * instead.
 */
class ButtonStack {
public:
  /**
   * @brief ButtonStack, the default constructor which fills the stack with
   * empty buttons.
   */
  ButtonStack();
  /**
   * @brief N_BUTTONS, the maximum number of buttons in a stack.
   */
  static const int N_BUTTONS = 9;
  /**
   * @brief hasWhite, checks if a stack contains a white button.
   * @return true if the stack has a white button and false otherwise.
   */
  bool hasWhite() const;
  /**
   * @brief isEmpty, checks if the stack is empty. The current implementation
   * only checks that the first element of the stack is empty, as a LIFO
   * datastructure, this is sufficient.
   * @return true if the stack is empty and false otherwise.
   */
  bool isEmpty() const;
  /**
   * @brief nButtons, counts the number of non-empty buttons within a stack.
   * @return the number of non-empty buttons.
   */
  int nButtons() const;
  /**
   * @brief push, adds a new button onto the stack.
   * @param b, the button to push onto the stack.
   */
  void push(enum Button b);
  /**
   * @brief reset, resets the stacks by having only empty elements in it.
   */
  void reset();
  /**
   * @brief has2SameButtons, checks if the two top buttons are the same which is
   * useful for the replay rule of the game. To avoid a false positive on an
   * empty stack, the function checks that the number of non-empty buttons is
   * greater than 2.
   * @return true if the two (non-empty) top buttons of the stack are the same.
   */
  bool has2SameButtons();
  /**
   * @brief operator [], subscript operator overload to access data from the
   * underlying array.
   * @param idx, the index to access the data at.
   * @return the button at the given index.
   */
  enum Button operator[](int idx);

private:
  /**
   * @brief m_stackPointer, the pointer keeping track of the index in the stack.
   */
  int m_stackPointer = 0;
  /**
   * @brief m_stack, the hybrid stack array to store the data.
   */
  std::array<Button, N_BUTTONS> m_stack;
};

#endif // BUTTONSTACK_H
