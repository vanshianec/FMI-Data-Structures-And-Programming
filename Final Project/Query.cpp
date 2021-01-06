#ifndef _QUERY_CPP
#define _QUERY_CPP

#include <iostream>
#include <vector>
#include "Query.h"

Query::Query(const std::string& _tableName) : tableName(_tableName) {}

Query::~Query()
{

}

const std::string& Query::getTableName() const
{
    return tableName;
}

bool Query::areColumnsValuesValid(const std::vector<Scanner::Token>& values)
{
    for (const auto & columnValue : values)
    {
        int length = columnValue.value.length();
        if (length > maxStringValueLength)
        {
            std::cout << "Inserted string : [" << columnValue.value
                      << "] is too long, max allowed length is " << maxStringValueLength << " characters" << std::endl;
            return false;
        }
    }

    return true;
}

#endif

