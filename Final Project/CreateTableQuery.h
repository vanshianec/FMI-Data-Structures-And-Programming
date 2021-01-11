#ifndef _CREATEQUERY_H
#define _CREATEQUERY_H

#include "Query.h"
#include "TokenType.h"

class CreateTableQuery : public Query
{
private:
    std::vector<Token> columns;
    Token primaryKey;

public:
    CreateTableQuery(const std::string&, const std::vector<Token>&, const Token&);

    void accept(Executor*) override;
    const std::vector<Token>& getColumns() const;
    const Token& getPrimaryKey() const;
};

#endif
