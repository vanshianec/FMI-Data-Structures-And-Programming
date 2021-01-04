#ifndef _QUERY_CPP
#define _QUERY_CPP

#include "Query.h"

Query::Query(const std::string& _tableName) : tableName(_tableName) {}

Query::~Query()
{

}

const std::string& Query::getTableName() const
{
    return tableName;
}

#endif

