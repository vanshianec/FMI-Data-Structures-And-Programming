#ifndef _SELECT_QUERY_H
#define _SELECT_QUERY_H

#include "Query.h"
#include "TokenType.h"
#include <vector>

class SelectQuery : public Query
{
private:
    std::vector<std::string> columnNames;
    std::vector<TokenType> aggregates;
    std::string whereColumn;
    TokenType whereOp;
    std::string whereValue;
    std::string orderByColumn;
    TokenType orderType;

public:
    SelectQuery(const std::string&, const std::vector<std::string>&, const std::vector<TokenType>&,
                const std::string&, const TokenType&, const std::string&, const std::string&, const TokenType&);

    void accept(Executor&) override;

    const std::vector<std::string>& getColumnNames() const;
    const std::vector<TokenType>& getAggregates() const;
    const std::string& getWhereColumn() const;
    TokenType getWhereOp() const;
    const std::string& getWhereValue() const;
    const std::string& getOrderByColumn() const;
    TokenType getOrderType() const;
};

#endif
