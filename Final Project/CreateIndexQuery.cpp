#ifndef _CREATE_QUERY_CPP
#define _CREATE_QUERY_CPP

#include "CreateIndexQuery.h"
#include "Executor.h"

CreateIndexQuery::CreateIndexQuery(const std::string& _tableName, const std::string& _columnName) : Query(_tableName)
{
    columnName = _columnName;
}

void CreateIndexQuery::accept(Executor* executor)
{
    executor->execute(*this);
}

const std::string& CreateIndexQuery::getColumnName() const
{
    return columnName;
}

#endif

