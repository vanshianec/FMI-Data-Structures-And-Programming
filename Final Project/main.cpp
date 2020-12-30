#include <iostream>
#include "Parser.h"

int main()
{
    Parser parser(std::cin);
    parser.parseQuery();

    return 0;
}
