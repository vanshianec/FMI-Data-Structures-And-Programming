#ifndef _UPDATE_QUERY_CPP
#define _UPDATE_QUERY_CPP

#include "UpdateQuery.h"
#include "Executor.h"

UpdateQuery::UpdateQuery(const std::string& _tableName, const std::vector<std::string>& _columnNames,
                         const std::vector<Token>& _columnValues, const std::string& _whereColumn,
                         const TokenType& _op, const Token& _value) : Query(_tableName)
{
    validateColumnValues(_columnValues);
    columnNames = _columnNames;
    columnValues = _columnValues;
    whereColumn = _whereColumn;
    op = _op;
    whereValue = _value;
}

void UpdateQuery::accept(Executor* executor)
{
    executor->execute(*this);
}

const std::vector<std::string>& UpdateQuery::getColumnNames() const
{
    return columnNames;
}

const std::vector<Token>& UpdateQuery::getColumnValues() const
{
    return columnValues;
}

const std::string& UpdateQuery::getWhereColumn() const
{
    return whereColumn;
}

TokenType UpdateQuery::getOp() const
{
    return op;
}

const Token& UpdateQuery::getWhereValue() const
{
    return whereValue;
}

#endif

