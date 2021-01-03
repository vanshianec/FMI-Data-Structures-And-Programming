#include <iostream>
#include "Parser.h"

int main()
{
    std::string str;
    Parser parser(std::cin);
    Query* query = parser.parseQuery();
    while (query != nullptr)
    {
        query->execute();
        query = parser.parseQuery();
    }

    return 0;
}
