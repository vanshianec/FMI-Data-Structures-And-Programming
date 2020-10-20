#ifndef DLINKEDLIST_CPP
#define DLINKEDLIST_CPP

#include <stdexcept>
#include <unordered_set>
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
int DLinkedList<T>::size() const
{
    int length = 0;
    Node* current = first;
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
T& DLinkedList<T>::front()
{
    if (isEmpty())
    {
        throw std::out_of_range("The list is empty!");
    }

    return first->data;
}

template<class T>
T& DLinkedList<T>::back()
{
    if (isEmpty())
    {
        throw std::out_of_range("The list is empty!");
    }

    return last->data;
}

template<class T>
T& DLinkedList<T>::get(int index)
{
    Node* current = getNode(index);
    return current->data;
}

template<class T>
void DLinkedList<T>::insertFront(const T& data)
{
    first = new Node(data, nullptr, first);

    if (first->next != nullptr)
    {
        first->next->prev = first;
    }
    else
    {
        last = first;
    }
}

template<class T>
void DLinkedList<T>::insertBack(const T& data)
{
    last = new Node(data, last, nullptr);

    if (last->prev != nullptr)
    {
        last->prev->next = last;
    }
    else
    {
        first = last;
    }
}

template<class T>
void DLinkedList<T>::insertAt(int index, const T& data)
{
    if (index == size())
    {
        insertBack(data);
        return;
    }

    Node* current = getNode(index);
    insertNodeAt(current, data);
}

template<class T>
T DLinkedList<T>::removeFront()
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty!");
    }

    T data = first->data;
    deleteNode(first);
    return data;
}

template<class T>
T DLinkedList<T>::removeBack()
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty!");
    }

    T data = last->data;
    deleteNode(last);
    return data;
}

template<class T>
T DLinkedList<T>::deleteAt(int index)
{
    Node* current = getNode(index);
    T data = current->data;
    deleteNode(current);
    return data;
}

template<class T>
void DLinkedList<T>::swap(int firstIndex, int secondIndex)
{
    if (firstIndex > secondIndex)
    {
        throw std::invalid_argument("Start index should be less or equal to endIndex");
    }

    Node* firstNode = getNode(firstIndex);
    Node* secondNode = getNode(secondIndex);

    T temp = firstNode->data;
    firstNode->data = secondNode->data;
    secondNode->data = temp;
}

template<class T>
void DLinkedList<T>::removeDuplicates()
{
    std::unordered_set<T> set;
    Node* current = first;
    Node* prev = nullptr;
    while (current != nullptr)
    {
        if (set.find(current->data) != set.end())
        {
            deleteNode(current);
        }
        else
        {
            set.insert(current->data);
            prev = current;
        }

        current = prev->next;
    }
}

template<class T>
void DLinkedList<T>::removeAll(const T& data)
{
    Node* current = first, * next;
    while (current != nullptr)
    {
        next = current->next;
        if (current->data == data)
        {
            deleteNode(current);
        }
        current = next;
    }
}

template<class T>
void DLinkedList<T>::reverse()
{
    Node* current = first;
    first = last;
    last = current;
    Node* next = nullptr;
    while (current != nullptr)
    {
        next = current->next;
        current->next = current->prev;
        current->prev = next;
        current = next;
    }
}

template<class T>
DLinkedList<T>& DLinkedList<T>::operator+=(const T& data)
{
    insertBack(data);
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
int DLinkedList<T>::count(Node* start, const T& element) const
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
DLinkedList<T>::Iterator::Iterator(Node* _current) : current(_current) {}

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
typename DLinkedList<T>::Iterator DLinkedList<T>::begin(Node* start)
{
    Node* current = first;
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
typename DLinkedList<T>::Node* DLinkedList<T>::getNode(int index)
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty!");
    }

    if (index < 0)
    {
        throw std::invalid_argument("Index should be positive!");
    }

    Node* current = first;
    while (current->next != nullptr && index != 0)
    {
        current = current->next;
        index--;
    }

    if (index > 0)
    {
        throw std::invalid_argument("Index out of range!");
    }

    return current;
}

template<class T>
void DLinkedList<T>::insertNodeAt(Node* position, const T& data)
{
    if (position == nullptr)
    {
        return;
    }

    Node* newNode = new Node(data, position->prev, position);

    if (position == first)
    {
        first = newNode;
    }
    else
    {
        position->prev->next = newNode;
    }

    position->prev = newNode;
}

template<class T>
void DLinkedList<T>::deleteNode(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node == first)
    {
        first = node->next;
    }
    else
    {
        node->prev->next = node->next;
    }

    if (node == last)
    {
        last = node->prev;
    }
    else
    {
        node->next->prev = node->prev;
    }

    delete node;
}

template<class T>
void DLinkedList<T>::copy(const DLinkedList& other)
{
    first = nullptr;
    last = nullptr;
    Node* current = other.first;
    while (current != nullptr)
    {
        insertBack(current->data);
        current = current->next;
    }
}

template<class T>
void DLinkedList<T>::clear()
{
    Node* current = first, * save;

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
    typename DLinkedList<T>::Node* current = list.first;
    while (current != nullptr)
    {
        out << current->data << " ";
        current = current->next;
    }

    return out;
}

#endif