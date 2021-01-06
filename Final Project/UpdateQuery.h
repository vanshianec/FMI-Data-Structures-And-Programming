#ifndef _UPDATE_QUERY_H
#define _UPDATE_QUERY_H

#include <vector>
#include "Query.h"
#include "TokenType.h"

class UpdateQuery : public Query
{
private:
    std::vector<std::string> columnNames;
    std::vector<Scanner::Token> columnValues;
    std::string whereColumn;
    TokenType op;
    Scanner::Token whereValue;

public:
    UpdateQuery(const std::string&, const std::vector<std::string>&, const std::vector<Scanner::Token>&,
                const std::string&, const TokenType&, const Scanner::Token&);

    void accept(Executor&) override;

    const std::vector<std::string>& getColumnNames() const;
    const std::vector<Scanner::Token>& getColumnValues() const;
    const std::string& getWhereColumn() const;
    TokenType getOp() const;
    const Scanner::Token& getWhereValue() const;
};

#endif
