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

    void writeColumnArgument(const std::string&, const TokenType&);
    int readTableColumns(int, const std::string&, std::vector<TokenType>&, std::vector<std::string>&);
    std::string readColumnValue(const TokenType&);
    bool openTableFile(const Query*);
    int readColumnsSize();
    bool readColumnsTypes(int columnsSize, const std::vector<Scanner::Token>&, std::vector<TokenType>&);
    bool validateQueryColumnArguments(const std::vector<Scanner::Token>&, const std::vector<std::string>&,
                                      const std::vector<TokenType>&, const std::vector<std::string>&,
                                      std::map<int, std::string>&, std::map<int, Scanner::Token>&) const;

    void readPrimaryKey();
    void updateRows(int columnsSize, const Scanner::Token&, const TokenType&, const std::vector<TokenType>&, int,
                    std::map<int, std::string>&, std::map<int, Scanner::Token>&);
    bool
    validateQueryColumnNames(const std::vector<std::string>& queryColumnNames,
                             const std::vector<std::string>& columnNames) const;
};

bool validateArgumentType(const std::vector<Scanner::Token>&, const TokenType&, int, const std::string&);
bool isWhereConditionMet(const std::string&, const TokenType&, const Scanner::Token&, const TokenType&);
bool isMoreThan(const std::string&, const Scanner::Token&);
bool isLessThan(const std::string&, const Scanner::Token&);
bool areValuesEqual(const std::string&, const Scanner::Token&);

#endif
