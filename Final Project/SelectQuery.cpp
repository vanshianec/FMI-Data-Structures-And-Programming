#ifndef _SELECT_QUERY_CPP
#define _SELECT_QUERY_CPP

#include "SelectQuery.h"
#include "Executor.h"

SelectQuery::SelectQuery(const std::string& _tableName, const std::vector<std::string>& _columnNames,
                         const std::vector<TokenType>& _aggregates, const std::string& _whereColumn,
                         const TokenType& _whereOp, const std::string& _whereValue,
                         const std::string& _orderByColumn, const TokenType& _orderType) : Query(_tableName)
{
    columnNames = _columnNames;
    aggregates = _aggregates;
    whereColumn = _whereColumn;
    whereOp = _whereOp;
    whereValue = _whereValue;
    orderByColumn = _orderByColumn;
    orderType = _orderType;
}

void SelectQuery::accept(Executor& executor)
{
    executor.execute(*this);
}

#endif

