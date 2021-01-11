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

void Query::validateColumnValues(const std::vector<Token>& values)
{
    for (const auto& columnValue : values)
    {
        int length = columnValue.value.length();
        if (length > maxStringValueLength)
        {
            std::string message = "Inserted string : [" + columnValue.value + "] is too long, max allowed length is "
                                  + std::to_string(maxStringValueLength) + " characters";
            throw std::invalid_argument(message);
        }
    }
}

#endif

