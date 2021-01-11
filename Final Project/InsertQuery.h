#ifndef _INSERT_QUERY_H
#define _INSERT_QUERY_H

#include "Query.h"

class InsertQuery : public Query
{
private:
    std::vector<Token> columnValues;

public:
    InsertQuery(const std::string&, const std::vector<Token>&);

    void accept(Executor*) override;
    const std::vector<Token>& getInsertValues() const;
};

#endif
