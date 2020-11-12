#ifndef _BINARYTREE_H
#define _BINARYTREE_H

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
    int searchCount(Node*, bool (*pred)(const T&)) const;
    int height(Node*) const;
    int countLeaves(Node*) const;
    T maxLeaf(Node*) const;
};

#include "BinaryTree.cpp"

#endif
