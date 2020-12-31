#include <iostream>
#include "Parser.h"

int main()
{
    std::string str;
    Parser parser(std::cin);
    parser.parseQuery();

    return 0;
}
