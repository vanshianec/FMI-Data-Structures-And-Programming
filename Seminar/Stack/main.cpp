#include <iostream>
#include "stack.h"

int main()
{
    Stack<int> stack;
    std::cout << stack.empty() << std::endl;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << stack.peek() << std::endl;
}
