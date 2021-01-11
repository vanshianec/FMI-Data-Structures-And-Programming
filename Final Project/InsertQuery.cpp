#ifndef _INSERT_QUERY_CPP
#define _INSERT_QUERY_CPP

#include <iostream>
#include "InsertQuery.h"
#include "Executor.h"

InsertQuery::InsertQuery(const std::string& _tableName, const std::vector<Token>& _columnValues)
        : Query(_tableName)
{
    validateColumnValues(_columnValues);
    columnValues = _columnValues;
}

void InsertQuery::accept(Executor* executor)
{
    executor->execute(*this);
}

const std::vector<Token>& InsertQuery::getInsertValues() const
{
    return columnValues;
}

#endif