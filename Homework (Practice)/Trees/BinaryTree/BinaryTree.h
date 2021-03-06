#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <vector>
#include <string>
#include <stack>

template<class T>
class BinTree
{

public:
    BinTree();
    ~BinTree();
    void insert(const T& value, const char *trace);
    T operator[](const char *trace) const;
    void print() const;
    int count() const;
    int searchCount(bool (*pred)(const T&)) const;
    int height() const;
    int countLeaves() const;
    T maxLeaf() const;
    std::vector<T> listLeaves() const;
    std::string findTrace(const T& x) const;
    T getAt(int index) const;

private:
    struct Node
    {
        T value;
        Node *left, *right;
    };

    Node *root;
    Node *insert(Node *current, const T& value, const char *trace);
    void print(Node *current, int spaces) const;
    void clearTree(Node *);
    int count(Node *) const;
    int searchCount(Node *, bool (*pred)(const T&)) const;
    int height(Node *) const;
    int countLeaves(Node *) const;
    T maxLeaf(Node *) const;
    void listLeaves(std::vector<T>& leaves, Node *current) const;
    bool findTrace(std::string& trace, Node *current, const T& x) const;
    T getAt(Node *, int index, int& count) const;

public:
    class Position
    {
    public:
        Position(Node *&);
        Position left() const;
        Position right() const;
        T get() const;
        void set(const T&);
        bool empty() const;

    private:
        Node *& current;
    };

    Position rootPosition();

    class Iterator
    {
    public:
        Iterator(Node *);

        Iterator& operator++();
        T operator*() const;
        bool operator!=(const Iterator&) const;

    private:
        std::stack<Node *> s;
    };

    Iterator begin();
    Iterator end();

};

#include "BinaryTree.cpp"

#endif
