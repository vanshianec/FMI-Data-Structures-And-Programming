#ifndef _INSERT_QUERY_H
#define _INSERT_QUERY_H

#include <vector>
#include "Query.h"

class InsertQuery : public Query
{
private:
    std::vector<std::string> columnValues;

public:
    InsertQuery(const std::string&, const std::vector<std::string>&);

    void accept(Executor&) override;
};

#endif
