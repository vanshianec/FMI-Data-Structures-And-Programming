#include "queue.h"
#include <stdexcept>

template<class T>
void Queue<T>::copy(const Queue<T>& other)
{
    Node *current = other.first;
    while (current != nullptr)
    {
        push_back(current->data);
        current = current->next;
    }
}

template<class T>
void Queue<T>::clear()
{
    while (pop()) {}
}

template<class T>
Queue<T>::Queue() : first(nullptr), last(nullptr) {}


template<class T>
Queue<T>::Queue(const Queue<T>& other) : first(nullptr), last(nullptr)
{
    copy(other);
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if (this != other)
    {
        clear();
        copy(other);
    }

    return *this;
}

template<class T>
T& Queue<T>::peek()
{
    if (empty())
    {
        throw std::runtime_error("Queue is empty!");
    }

    return first->data;
}

template<class T>
void Queue<T>::push_back(const T& data)
{
    Node* temp = new Node{data, nullptr};
    if (first == nullptr)
    {
        first = temp;
    }
    else
    {
        last->next = temp;
    }

    last = temp;
}

template<class T>
bool Queue<T>::pop()
{
    if (empty())
    {
        return false;
    }

    Node *temp = first;
    first = first->next;
    delete temp;

    if (empty())
    {
        last = nullptr;
    }

    return true;
}

template<class T>
bool Queue<T>::empty() const
{
    return first == nullptr;
}

