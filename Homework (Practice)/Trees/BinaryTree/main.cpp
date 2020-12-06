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
    std::cout << tree.count() << std::endl;
    std::cout << tree.searchCount(isEven) << std::endl;
    std::cout << tree.height() << std::endl;
    std::cout << tree.countLeaves() << std::endl;
    std::cout << tree.maxLeaf() << std::endl;

    std::vector<int> leaves = tree.listLeaves();
    for (int leaf : leaves)
    {
        std::cout << leaf << " ";
    }
    std::cout << std::endl;

    std::cout << tree.findTrace(222) << std::endl;

    std::cout << tree.getAt(5) << std::endl;

}
