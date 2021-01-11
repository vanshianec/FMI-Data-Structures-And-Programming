#ifndef _QUERY_EXECUTOR_H
#define _QUERY_EXECUTOR_H

#include <fstream>
#include "Executor.h"
#include <map>
#include <unordered_map>
#include <set>

class QueryExecutor : public Executor
{
private:
    std::fstream fileStream;
    void writeInsertArgument(const std::string&, const TokenType&);
    int findColumnIndex(int, const std::string&, std::vector<TokenType>&, std::vector<std::string>&);
    std::string readColumnValue(const TokenType&);
    void openTableFile(const std::string&);
    int readColumnsSize();
    void readTableColumns(int columnsSize, const std::vector<Token>& insertValues,
                          std::vector<std::string>& columnNames, std::vector<TokenType>& columnTypes);
    void updateRows(int columnsSize, const Token&, const TokenType&, const std::vector<TokenType>&, int,
                    std::unordered_map<int, std::string>&, std::unordered_map<int, Token>&);
    void validateArgumentType(const Token&, const TokenType&, const std::string&);
    void readRowsToSelect(const SelectQuery&, int, const std::vector<std::string>&,
                          const std::vector<TokenType>&, const Token&, int, std::unordered_map<int, std::string>&);
    void readPrimaryKeyValues(int, const std::vector<TokenType>&, const std::vector<std::string>&,
                              const Token&, std::set<std::string>&);
    void checkForDuplicateValue(int, const std::vector<Token>&, const std::vector<std::string>&,
                                const Token&, const std::set<std::string>&);
public:
    void execute(CreateTableQuery&) override;
    void execute(CreateIndexQuery&) override;
    void execute(InsertQuery&) override;
    void execute(UpdateQuery&) override;
    void execute(SelectQuery&) override;
};

void error(const std::string&);
bool fileExists(const char*);
bool isWhereConditionMet(const std::string&, const TokenType&, const Token&);
bool isMoreThan(const std::string&, const Token&);
bool isLessThan(const std::string&, const Token&);
bool areValuesEqual(const std::string&, const Token&);
bool validateWhereColumn(const std::string&, const std::vector<TokenType>&, int, const Token&);
bool validateQueryColumnArguments(const std::vector<Token>&, const std::vector<std::string>&,
                                  const std::vector<TokenType>&, const std::vector<std::string>&,
                                  std::unordered_map<int, std::string>&, std::unordered_map<int, Token>&);
bool
validateQueryColumnNames(std::unordered_map<int, std::string>&, const std::vector<std::string>&,
                         const std::vector<std::string>&);
void printSelectedRows(const std::vector<std::vector<Token>>&);
void writeStringValue(std::fstream&, const std::string&);
void aggregateRows(const std::vector<TokenType>&, std::vector<std::vector<Token>>&);

#endif
