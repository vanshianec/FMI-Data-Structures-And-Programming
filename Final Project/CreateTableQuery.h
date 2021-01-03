#ifndef _CREATEQUERY_H
#define _CREATEQUERY_H

#include <vector>
#include "Query.h"
#include "TokenType.h"

class CreateTableQuery : public Query
{
private:
    std::vector<std::string> columnNames;
    std::vector<TokenType> columnTypes;
    std::string primaryKey;

public:
    CreateTableQuery(const std::string&, const std::vector<std::string>&, const std::vector<TokenType>&,
                     const std::string&);

    void accept(Executor&) override;
};

#endif
