#include <iostream>
#include "Parser.h"
#include "QueryExecutor.h"

int main()
{
    std::string str;
    Parser parser(std::cin);
    Executor* executor = new QueryExecutor();

    while (true)
    {
        Query* query;
        try
        {
            query = parser.parseQuery();
        }
        catch (std::invalid_argument& ex)
        {
            std::cout << ex.what() << std::endl;
            continue;
        }

        if (query == nullptr)
        {
            break;
        }

        try
        {
            query->accept(executor);
        }
        catch (std::invalid_argument& ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

    delete executor;
    std::cout << "Exitting. Good bye!" << std::endl;
    return 0;
}
