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
    virtual void execute(SelectQuery&) = 0;
    virtual void execute(CreateTableQuery&) = 0;
    virtual void execute(CreateIndexQuery&) = 0;
    virtual void execute(InsertQuery&) = 0;
    virtual void execute(UpdateQuery&) = 0;
};

#endif
