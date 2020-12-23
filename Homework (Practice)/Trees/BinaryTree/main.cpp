#include <iostream>
#include "BinaryTree.h"

template<class T>
bool isEven(T num)
{
    return num % 2 == 0;
}

int main()
{
    BinTree<int> tree;
    tree.insert(5, "");
    tree.insert(63, "L");
    tree.insert(11, "R");
    tree.insert(66, "RR");
    tree.insert(333, "LL");
    tree.insert(222, "LLR");
    tree.insert(999, "LR");
    tree.insert(3833, "LRR");
    tree.print();
    std::cout << std::endl;

    BinTree<int> tree2;
    BinTree<int>::Position root = tree2.rootPosition();
    root.set(5);
    root.left().set(63);
    root.right().set(11);
    root.right().right().set(66);
    root.left().left().set(333);
    root.left().left().right().set(222);
    root.left().right().set(999);
    root.left().right().right().set(3833);
    tree2.print();

    BinTree<int>::Iterator it = tree.begin();
    BinTree<int>::Iterator end = tree.end();
    while (it != end)
    {
        std::cout << *it << "  ";
        ++it;
    }

    std::cout << std::endl;

    std::cout << tree.count() << " - " << tree2.count() << std::endl;
    std::cout << tree.searchCount(isEven) << " - " << tree2.searchCount(isEven) << std::endl;
    std::cout << tree.height() << " - " << tree2.height() << std::endl;
    std::cout << tree.countLeaves() << " - " << tree2.countLeaves() << std::endl;
    std::cout << tree.maxLeaf() << " - " << tree2.maxLeaf() << std::endl;

    std::vector<int> leaves = tree.listLeaves();
    for (int leaf : leaves)
    {
        std::cout << leaf << " ";
    }
    std::cout << std::endl;

    std::cout << tree.findTrace(222) << std::endl;

    std::cout << tree.getAt(5) << std::endl;

}
