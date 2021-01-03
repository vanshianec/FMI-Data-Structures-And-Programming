#ifndef _UPDATE_QUERY_H
#define _UPDATE_QUERY_H

#include <vector>
#include "Query.h"
#include "TokenType.h"

class UpdateQuery : public Query
{
private:
    std::vector<std::string> columnNames;
    std::vector<std::string> columnValues;
    std::string keyColumn;
    TokenType op;
    std::string value;

public:
    UpdateQuery(const std::string&, const std::vector<std::string>&, const std::vector<std::string>&,
                const std::string&, const TokenType&, const std::string&);

    void accept(Executor&) override;
};

#endif
