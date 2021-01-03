#ifndef _QUERY_H
#define _QUERY_H

#include "Executable.h"
#include <string>

class Query : Executable
{
private:
    std::string tableName;
protected:
    Query(const std::string&);

public:
    virtual void accept(Executor&) = 0;
    virtual ~Query();
};

#endif
