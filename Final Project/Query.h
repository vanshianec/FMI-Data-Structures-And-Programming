#ifndef _QUERY_H
#define _QUERY_H

#include "Executable.h"
#include "Scanner.h"
#include <string>

class Query : Executable
{
private:
    std::string tableName;

protected:
    Query(const std::string&);
    static bool areColumnsValuesValid(const std::vector<Scanner::Token>&);

public:
    virtual void accept(Executor&) = 0;
    const std::string& getTableName() const;
    static const int maxStringValueLength = 64;
    virtual ~Query();
};

#endif
