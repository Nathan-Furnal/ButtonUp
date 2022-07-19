#include "button.h"
#include "buttonstack.h"

ButtonStack::ButtonStack(enum Button b){
    push(b);
}

constexpr bool ButtonStack::isEmpty(){
    return m_stack[0] == Button::EMPTY;
}

constexpr bool ButtonStack::hasWhite(){
    for(auto const el : m_stack){
        if(el == Button::WHITE)
            return true;
    }
    return false;
}

constexpr int ButtonStack::nButtons(){
    return m_stackPointer;
}

void ButtonStack::push(enum Button b){
    if(b != Button::EMPTY){
        m_stack[m_stackPointer++] = b;
    }
}

constexpr Button ButtonStack::pop(){
    if(!isEmpty()){
    Button b = m_stack[m_stackPointer];
    m_stack[m_stackPointer--] = Button::EMPTY;
    return b;
    }
    else{
        return Button::EMPTY;
    }
}

void ButtonStack::reset(){
    m_stackPointer = 0;
    m_stack.fill(Button::EMPTY);
}

void ButtonStack::stackOnto(ButtonStack &otherStack){
   int i = 0;
   Button b = m_stack[i];
   while(b != Button::EMPTY){
       otherStack.push(b);
       b = m_stack[++i];
   }
   reset();
}

enum Button& ButtonStack::operator[](int idx){
    return m_stack[idx];
}
