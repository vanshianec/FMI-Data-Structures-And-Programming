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
};

#endif
