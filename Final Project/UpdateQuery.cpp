#ifndef _UPDATE_QUERY_CPP
#define _UPDATE_QUERY_CPP

#include "UpdateQuery.h"
#include "Executor.h"

UpdateQuery::UpdateQuery(const std::string& _tableName, const std::vector<std::string>& _columnNames,
                         const std::vector<std::string>& _columnValues, const std::string& _keyColumn,
                         const TokenType& _op, const std::string& _value) : Query(_tableName)
{
    columnNames = _columnNames;
    columnValues = _columnValues;
    keyColumn = _keyColumn;
    op = _op;
    value = _value;
}

void UpdateQuery::accept(Executor& executor)
{
    executor.execute(*this);
}

#endif

