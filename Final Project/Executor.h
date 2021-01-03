#ifndef _EXECUTOR_H
#define _EXECUTOR_H

#include "SelectQuery.h"
#include "CreateTableQuery.h"
#include "CreateIndexQuery.h"
#include "InsertQuery.h"
#include "UpdateQuery.h"

class Executor
{
public:
    void execute(SelectQuery&);
    void execute(CreateTableQuery&);
    void execute(CreateIndexQuery&);
    void execute(InsertQuery&);
    void execute(UpdateQuery&);
};

#endif
