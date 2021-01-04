#ifndef _INSERT_QUERY_H
#define _INSERT_QUERY_H

#include <vector>
#include "Query.h"
#include "Scanner.h"

class InsertQuery : public Query
{
private:
    std::vector<Scanner::Token> columnValues;

public:
    InsertQuery(const std::string&, const std::vector<Scanner::Token>&);

    void accept(Executor&) override;
    const std::vector<Scanner::Token>& getColumnValues() const;
};

#endif
