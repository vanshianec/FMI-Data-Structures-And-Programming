#include "stack.h"
#include <stdexcept>

template<class T>
Stack<T>::Stack() : top(nullptr) {}

template<class T>
Stack<T>::~Stack()
{
    while(pop()){}
}

template<class T>
T& Stack<T>::peek() const
{
    if(empty())
    {
        throw std::runtime_error("Stack is empty!");
    }

    return top->data;
}

template<class T>
bool Stack<T>::pop()
{
    if (empty())
    {
        return false;
    }

    Node *temp = top;
    top = top->next;
    delete temp;

    return true;
}

template<class T>
void Stack<T>::push(const T& data)
{
    top = new Node{data, top};
}

template<class T>
bool Stack<T>::empty() const
{
    return top == nullptr;
}