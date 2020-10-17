#ifndef DLINKEDLIST_CPP
#define DLINKEDLIST_CPP

#include <stdexcept>
#include "DLinkedList.h"

template<class T>
DLinkedList<T>::DLinkedList() : first(nullptr), last(nullptr) {}

template<class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T>& other)
{
    copy(other);
}

template<class T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList<T>& other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}

template<class T>
DLinkedList<T>::~DLinkedList()
{
    clear();
}

template<class T>
void DLinkedList<T>::insertStart(const T& data)
{
    first = new Node(data, nullptr, first);

    if (first->next != nullptr)
    {
        first->next->prev = first;
    } else
    {
        last = first;
    }
}

template<class T>
void DLinkedList<T>::insertEnd(const T& data)
{
    last = new Node(data, last, nullptr);

    if (last->prev != nullptr)
    {
        last->prev->next = last;
    } else
    {
        first = last;
    }
}

template<class T>
void DLinkedList<T>::insertAt(const T& data, int index)
{
    if (index < 0)
    {
        throw std::out_of_range("Index should be positive!");
    }

    if (first == nullptr)
    {
        if (index > 0)
        {
            throw std::out_of_range("Index out of range!");
        }

        first = new Node(data, nullptr, nullptr);
        last = first;
        return;
    }

    Node *current = first;
    while (current != nullptr && index != 0)
    {
        index--;
        current = current->next;
    }

    if (index > 0)
    {
        throw std::out_of_range("Index out of range!");
    }

    Node *temp = current->prev;
    Node *newNode = new Node(data, temp, current);
    if (temp != nullptr)
    {
        temp->next = newNode;
    }
    current->prev = newNode;
}

template<class T>
DLinkedList<T>& DLinkedList<T>::operator+=(const T& data)
{
    insertEnd(data);
    return *this;
}

template<class T>
DLinkedList<T> DLinkedList<T>::operator+(const T& data) const
{
    DLinkedList<T> copy(*this);
    copy += data;
    return copy;
}

template<class T>
int DLinkedList<T>::length() const
{
    int length = 0;
    Node *current = first;
    while (current != nullptr)
    {
        length++;
        current = current->next;
    }

    return length;
}

template<class T>
bool DLinkedList<T>::isEmpty() const
{
    return first == nullptr;
}

template<class T>
int DLinkedList<T>::count(Node *start, const T& element) const
{
    DLinkedList<T>::Iterator it = this->begin(start);
    DLinkedList<T>::Iterator end = this->end();
    int count = 0;
    while (it != end)
    {
        if (*it == element)
        {
            count++;
        }
        ++it;
    }

    return count;
}

template<class T>
DLinkedList<T>::Iterator::Iterator(Node *_current) : current(_current) {}

template<class T>
T& DLinkedList<T>::Iterator::operator*()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Null iterator");
    }

    return current->data;
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Null iterator");
    }

    current = current->next;
    return *this;
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const Iterator& other)
{
    return current != other.current;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::begin()
{
    return DLinkedList<T>::Iterator(first);
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::begin(Node *start)
{
    Node *current = first;
    while (current != nullptr)
    {
        if (current == start)
        {
            return DLinkedList<T>::Iterator(current);
        }

        current = current->next;
    }

    return DLinkedList<T>::Iterator(nullptr);;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::end()
{
    return DLinkedList<T>::Iterator(nullptr);
}

template<class T>
void DLinkedList<T>::copy(const DLinkedList& other)
{
    if (other.first == nullptr)
    {
        first = nullptr;
        last = nullptr;
        return;
    }

    Node *otherCurrent = other.first;
    first = new Node();
    Node *thisCurrent = first;
    while (otherCurrent != nullptr)
    {
        thisCurrent->data = otherCurrent->data;
        if (otherCurrent->next != nullptr)
        {
            thisCurrent->next = new Node();
            thisCurrent->next->prev = thisCurrent;
        }

        otherCurrent = otherCurrent->next;
    }

    last = thisCurrent;
}

template<class T>
void DLinkedList<T>::clear()
{
    Node *current = first, *save;

    while (current != nullptr)
    {
        save = current;
        current = current->next;
        delete save;
    }

    first = nullptr;
    last = nullptr;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const DLinkedList<T>& list)
{
    typename DLinkedList<T>::Node *current = list.first;
    while (current != nullptr)
    {
        out << current->data << " ";
        current = current->next;
    }

    return out;
}

#endif