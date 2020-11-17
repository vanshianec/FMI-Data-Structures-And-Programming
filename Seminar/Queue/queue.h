#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

template<class T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
    };

    Node *first;
    Node *last;

    void copy(const Queue<T>&);
    void clear();

public:
    Queue();
    Queue(const Queue<T>&);
    Queue<T>& operator=(const Queue<T>&);
    ~Queue() { clear(); }

    T& peek();
    void push_back(const T&);
    bool pop();
    bool empty() const;
};

#include "queue.cpp"

#endif
