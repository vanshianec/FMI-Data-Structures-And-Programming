#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

template<class T>
class DLinkedList
{
private:
    struct Node
    {
        Node() : prev(nullptr), next(nullptr) {}

        Node(const T& _data, Node *_prev, Node *_next) : data(_data), prev(_prev), next(_next) {}

        T data;
        Node *prev, *next;
    };

    Node *first;
    Node *last;

public:

    DLinkedList();
    DLinkedList(const DLinkedList&);
    DLinkedList& operator=(const DLinkedList&);
    ~DLinkedList();
    void insertStart(const T&);
    void insertEnd(const T&);
    void insertAt(const T&, int index);
    void deleteAt(int index);
    DLinkedList& operator+=(const T&);
    DLinkedList operator+(const T&) const;
    int length() const;
    bool isEmpty() const;
    int count(Node *start, const T& element) const;

    class Iterator
    {
    public:
        Iterator(Node *);
        T& operator*();
        Iterator& operator++();
        bool operator!=(const Iterator&);

    private:
        Node *current;
    };

    Iterator begin();
    Iterator begin(Node *);
    Iterator end();

private:
    template<class E>
    friend std::ostream& operator<<(std::ostream&, const DLinkedList<E>&);

    void copy(const DLinkedList&);
    void clear();
};

template<class T>
std::ostream& operator<<(std::ostream&, const DLinkedList<T>&);

#include "DLinkedList.cpp"

#endif
