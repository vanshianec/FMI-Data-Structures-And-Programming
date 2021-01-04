#ifndef _QUERY_EXECUTOR_H
#define _QUERY_EXECUTOR_H

#include <fstream>
#include "Executor.h"

class QueryExecutor : public Executor
{
private:
    std::fstream fileStream;

public:
    void execute(SelectQuery& selectQuery) override;
    void execute(CreateTableQuery& createTableQuery) override;
    void execute(CreateIndexQuery&) override;
    void execute(InsertQuery&) override;
    void execute(UpdateQuery&) override;
};

#endif
