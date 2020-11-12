#ifndef _BINARYTREE_CPP
#define _BINARYTREE_CPP

#include "BinaryTree.h"
#include <cassert>
#include <string>
#include <iostream>

template<class T>
BinTree<T>::BinTree() : root(nullptr) {}

template<class T>
BinTree<T>::~BinTree()
{
    clearTree(root);
}

template<class T>
void BinTree<T>::clearTree(Node *current)
{
    if (current == nullptr)
    {
        return;
    }

    clearTree(current->left);
    clearTree(current->right);
    delete current;
}

template<class T>
void BinTree<T>::insert(const T& value, const char *trace)
{
    root = insert(root, value, trace);
}

template<class T>
typename BinTree<T>::Node *BinTree<T>::insert(Node *current, const T& value, const char *trace)
{
    if (trace[0] == 0)
    {
        if (current == nullptr)
        {
            return new Node{value, nullptr, nullptr};
        }
        else
        {
            current->value = value;
        }
    }

    assert(trace[0] == 'L' || trace[0] == 'R');
    assert(current != nullptr);

    if (trace[0] == 'L')
    {
        current->left = insert(current->left, value, ++trace);
    }
    else
    {
        current->right = insert(current->right, value, ++trace);
    }

    return current;
}

template<class T>
T BinTree<T>::operator[](const char *trace) const
{

}

template<class T>
void BinTree<T>::print() const
{
    print(root, 0);
}

template<class T>
void BinTree<T>::print(Node *current, int spaces) const
{
    if (current == nullptr)
    {
        return;
    }

    print(current->left, spaces + 4);

    std::cout << std::string(spaces, ' ');
    std::cout << current->value;
    std::cout << std::endl;

    print(current->right, spaces + 4);
}

template<class T>
int BinTree<T>::count() const
{
    return count(root);
}

template<class T>
int BinTree<T>::count(Node *current) const
{
    if (current == nullptr)
    {
        return 0;
    }

    return 1 + count(current->left) + count(current->right);
}

template<class T>
int BinTree<T>::searchCount(bool (*pred)(const T&)) const
{
    return searchCount(root, pred);
}

template<class T>
int BinTree<T>::searchCount(Node *current, bool (*pred)(const T&)) const
{
    if (current == nullptr)
    {
        return 0;
    }

    int count = pred(current->value) ? 1 : 0;

    return count + searchCount(current->left, pred) + searchCount(current->right, pred);
}

template<class T>
int BinTree<T>::height() const
{
    return height(root);
}

template<class T>
int BinTree<T>::height(Node *current) const
{
    if (current == nullptr)
    {
        return 0;
    }

    return 1 + std::max(height(current->left), height(current->right));
}

template<class T>
int BinTree<T>::countLeaves() const
{
    return countLeaves(root);
}

template<class T>
int BinTree<T>::countLeaves(Node *current) const
{
    if (current == nullptr)
    {
        return 0;
    }

    if (current->left == nullptr && current->right == nullptr)
    {
        return 1;
    }

    return countLeaves(current->left) + countLeaves(current->right);
}

template<class T>
T BinTree<T>::maxLeaf() const
{
    return maxLeaf(root);
}

template<class T>
T BinTree<T>::maxLeaf(Node *current) const
{
    assert(current != nullptr);

    if (current->left == nullptr && current->right == nullptr)
    {
        return current->value;
    }
    else if (current->left == nullptr && current->right != nullptr)
    {
        return maxLeaf(current->right);
    }
    else if (current->left != nullptr && current->right == nullptr)
    {
        return maxLeaf(current->left);
    }

    return std::max(maxLeaf(current->left), maxLeaf(current->right));
}


#endif
