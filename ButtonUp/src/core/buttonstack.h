#ifndef BUTTONSTACK_H
#define BUTTONSTACK_H
#include <array>
#include "button.h"

class ButtonStack{
private:
    int m_stackPointer = 0;
    std::array<Button, 9> m_stack;

public:
    ButtonStack(enum Button b);
    constexpr bool hasWhite();
    constexpr bool isEmpty();
    constexpr int nButtons();
    void push(enum Button b);
    constexpr Button pop();
    void reset();
    void stackOnto(ButtonStack& bs);
    enum Button& operator[](int);
};

#endif // BUTTONSTACK_H
