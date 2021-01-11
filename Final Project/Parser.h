#ifndef _PARSER_H
#define _PARSER_H

#include <istream>
#include <vector>
#include "Scanner.h"
#include "Query.h"

class Parser
{
private:
    Scanner scanner;
    Token currentToken;
    Query* currentQuery;

    void consume(TokenType);
    void consumeDataType(Token&);
    void consumeColumnValue();
    void consumeOperator();
    void consumeAggregate();
    void parseCreateQuery();
    void parseInsertQuery();
    void parseUpdateQuery();
    void parseSelectQuery();
    void parseCreateTable();
    void parseCreateIndex();
    void parseSelectAggregate(std::vector<std::string>&, std::vector<TokenType>&);
    void parseSelectColumns(std::vector<std::string>&);
    void parseSelectAfterFrom(std::vector<std::string>&, std::vector<TokenType>&);
    void parseWhereClause(std::string&, Token&, TokenType&);
    void parseOrderByClause(std::string&, TokenType&);
    void assureSemiColumn() const;
    void deleteQuery();

public:
    Parser(std::istream&);
    Query* parseQuery();
    ~Parser();
    Token parsePrimaryColumn();
    void parseCreateTableColumns(std::vector<Token>&);
    void parseInsertColumns(std::vector<Token>& columnValues);
    void parseUpdateColumnsSet(std::vector<std::string>& columnNames, std::vector<Token>& columnValues);
};

void error(const char*);

#endif
