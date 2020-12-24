#include <iostream>

#include "hashmap.h"

int hash(int key)
{
    return key / 2;
}

int main()
{
    HashMap<int, std::string> map(10, hash);
    map[0] = "pesho";
    map[1] = "gosho";
    map[0] = "misho";
    map[3] = "tosho";
    map[4] = "a";
    map[5] = "f";
    map[6] = "g";

    std::cout << map[0] << std::endl;
    std::cout << map[1] << std::endl;
    std::cout << map[0] << std::endl;
    std::cout << map[3] << std::endl;
    std::cout << map[4] << std::endl;
    std::cout << map[5] << std::endl;
    std::cout << map[6] << std::endl;

    std::cout << std::endl;

    for (const int& key : map)
    {
        std::cout << map[key] << std::endl;
    }

    return 0;
}
