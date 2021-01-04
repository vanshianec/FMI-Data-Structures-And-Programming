#ifndef _INSERT_QUERY_CPP
#define _INSERT_QUERY_CPP

#include "InsertQuery.h"
#include "Executor.h"

InsertQuery::InsertQuery(const std::string& _tableName, const std::vector<Scanner::Token>& _columnValues)
        : Query(_tableName)
{
    columnValues = _columnValues;
}

void InsertQuery::accept(Executor& executor)
{
    executor.execute(*this);
}

const std::vector<Scanner::Token>& InsertQuery::getColumnValues() const
{
    return columnValues;
}


#endif