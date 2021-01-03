#ifndef _INSERT_QUERY_CPP
#define _INSERT_QUERY_CPP

#include "InsertQuery.h"
#include "Executor.h"

InsertQuery::InsertQuery(const std::string& _tableName, const std::vector<std::string>& _columnValues)
        : Query(_tableName)
{
    columnValues = _columnValues;
}

void InsertQuery::accept(Executor& executor)
{
    executor.execute(*this);
}


#endif