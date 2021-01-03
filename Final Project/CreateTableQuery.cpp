#ifndef _CREATE_QUERY_CPP
#define _CREATE_QUERY_CPP

#include "CreateTableQuery.h"
#include "Executor.h"

CreateTableQuery::CreateTableQuery(const std::string& _tableName, const std::vector<std::string>& _columnNames,
                                   const std::vector<TokenType>& _columnTypes, const std::string& _key) : Query(
        _tableName)
{
    columnNames = _columnNames;
    columnTypes = _columnTypes;
    primaryKey = _key;
}

void CreateTableQuery::accept(Executor& executor)
{
    executor.execute(*this);
}

#endif

