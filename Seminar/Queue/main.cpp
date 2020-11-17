#include <iostream>
#include "queue.h"

int main()
{
    Queue<int> queue;
    queue.push_back(1);
    queue.push_back(2);
    queue.push_back(3);
    queue.push_back(4);
    queue.push_back(5);

    std::cout << queue.peek() << std::endl;
    std::cout << queue.pop() << std::endl;
    std::cout << queue.peek() << std::endl;
    queue.pop();
    queue.pop();
    queue.pop();
    queue.pop();
    std::cout << queue.pop() << std::endl;
}
