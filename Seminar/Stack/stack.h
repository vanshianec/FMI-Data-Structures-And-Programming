#ifndef _STACK_H
#define _STACK_H

template<class T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node *next;
    };

    Node* top;

public:
    Stack();
    Stack(const Stack<T>&) = delete;
    Stack& operator=(const Stack<T>&) = delete;
    ~Stack();

    T& peek() const;
    bool pop();
    void push(const T&);
    bool empty() const;
};

#include "stack.cpp"

#endif
