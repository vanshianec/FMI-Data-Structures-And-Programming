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

const std::vector<std::string>& CreateTableQuery::getColumnNames() const
{
    return columnNames;
}

const std::vector<TokenType>& CreateTableQuery::getColumnTypes() const
{
    return columnTypes;
}

const std::string& CreateTableQuery::getPrimaryKey() const
{
    return primaryKey;
}

#endif

