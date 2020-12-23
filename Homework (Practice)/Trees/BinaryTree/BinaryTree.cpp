#ifndef _BINARYTREE_CPP
#define _BINARYTREE_CPP

#include "BinaryTree.h"
#include <cassert>
#include <string>
#include <iostream>
#include <algorithm>

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


template<class T>
std::vector<T> BinTree<T>::listLeaves() const
{
    std::vector<T> leaves;
    listLeaves(leaves, root);
    return leaves;
}

template<class T>
void BinTree<T>::listLeaves(std::vector<T>& leaves, Node *current) const
{
    if (current == nullptr)
    {
        return;
    }

    if (current->left == nullptr && current->right == nullptr)
    {
        leaves.push_back(current->value);
        return;
    }

    listLeaves(leaves, current->left);
    listLeaves(leaves, current->right);
}

template<class T>
std::string BinTree<T>::findTrace(const T& x) const
{
    std::string trace = "-";
    findTrace(trace, root, x);
    std::reverse(trace.begin(), trace.end());
    if (trace.size() > 1)
    {
        trace.pop_back();
    }
    return trace;
}

template<class T>
bool BinTree<T>::findTrace(std::string& trace, Node *current, const T& x) const
{
    if (current == nullptr)
    {
        return false;
    }

    if (current->value == x)
    {
        trace.push_back(' ');
        return true;
    }

    if (findTrace(trace, current->left, x))
    {
        trace.push_back('L');
        return true;
    }

    if (findTrace(trace, current->right, x))
    {
        trace.push_back('R');
        return true;
    }

    return false;
}

template<class T>
T BinTree<T>::getAt(int index) const
{
    int count = 0;
    return getAt(root, index, count);
}

template<class T>
T BinTree<T>::getAt(Node *current, int index, int& count) const
{
    if (current == nullptr)
    {
        count--;
        return -1;
    }

    if (count == index)
    {
        return current->value;
    }

    count++;
    T left = getAt(current->left, index, count);

    if (left == -1)
    {
        count++;
        return getAt(current->right, index, count);
    }

    return left;
}

template<class T>
typename BinTree<T>::Position BinTree<T>::rootPosition()
{
    return Position(root);
}

template<class T>
BinTree<T>::Position::Position(BinTree::Node *& node) : current(node) {}

template<class T>
typename BinTree<T>::Position BinTree<T>::Position::left() const
{
    assert(current != nullptr);
    return Position(current->left);
}

template<class T>
typename BinTree<T>::Position BinTree<T>::Position::right() const
{
    assert(current != nullptr);
    return Position(current->right);
}

template<class T>
T BinTree<T>::Position::get() const
{
    assert(current != nullptr);
    return current->value;
}

template<class T>
void BinTree<T>::Position::set(const T& value)
{
    if (current != nullptr)
    {
        current->value = value;
    }
    else
    {
        current = new Node{value, nullptr, nullptr};
    }
}

template<class T>
bool BinTree<T>::Position::empty() const
{
    return current == nullptr;
}

template<class T>
BinTree<T>::Iterator::Iterator(BinTree::Node *current)
{
    while (current != nullptr)
    {
        s.push(current);
        current = current->left;
    }
}

template<class T>
typename BinTree<T>::Iterator& BinTree<T>::Iterator::operator++()
{
    assert(!s.empty());

    BinTree<T>::Node *current = s.top()->right;
    s.pop();

    while (current != nullptr)
    {
        s.push(current);
        current = current->left;
    }

    return *this;
}

template<class T>
T BinTree<T>::Iterator::operator*() const
{
    return s.top()->value;
}

template<class T>
bool BinTree<T>::Iterator::operator!=(const BinTree::Iterator& other) const
{
    return s != other.s;
}

template<class T>
typename BinTree<T>::Iterator BinTree<T>::begin()
{
    return BinTree::Iterator(root);
}

template<class T>
typename BinTree<T>::Iterator BinTree<T>::end()
{
    return BinTree::Iterator(nullptr);
}

#endif

