#ifndef _CREATE_QUERY_CPP
#define _CREATE_QUERY_CPP

#include "CreateTableQuery.h"
#include "Executor.h"

CreateTableQuery::CreateTableQuery(const std::string& _tableName, const std::vector<Token>& _columns,
                                   const Token& _key) : Query(_tableName)
{
    columns = _columns;
    primaryKey = _key;
}

void CreateTableQuery::accept(Executor* executor)
{
    executor->execute(*this);
}

const std::vector<Token>& CreateTableQuery::getColumns() const
{
    return columns;
}

const Token& CreateTableQuery::getPrimaryKey() const
{
    return primaryKey;
}

#endif

