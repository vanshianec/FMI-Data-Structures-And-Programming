#ifndef _CREATE_INDEX_QUERY_H
#define _CREATE_INDEX_QUERY_H

#include "Query.h"

class CreateIndexQuery : public Query
{
private:
    std::string columnName;
public:
    const std::string& getColumnName() const;

public:
    CreateIndexQuery(const std::string&, const std::string&);
    void accept(Executor*) override;
};

#endif
