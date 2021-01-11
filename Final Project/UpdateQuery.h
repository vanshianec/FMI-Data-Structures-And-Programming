#ifndef _UPDATE_QUERY_H
#define _UPDATE_QUERY_H

#include "Query.h"
#include "TokenType.h"

class UpdateQuery : public Query
{
private:
    std::vector<std::string> columnNames;
    std::vector<Token> columnValues;
    std::string whereColumn;
    TokenType op;
    Token whereValue;

public:
    UpdateQuery(const std::string&, const std::vector<std::string>&, const std::vector<Token>&,
                const std::string&, const TokenType&, const Token&);

    void accept(Executor*) override;

    const std::vector<std::string>& getColumnNames() const;
    const std::vector<Token>& getColumnValues() const;
    const std::string& getWhereColumn() const;
    TokenType getOp() const;
    const Token& getWhereValue() const;
};

#endif
