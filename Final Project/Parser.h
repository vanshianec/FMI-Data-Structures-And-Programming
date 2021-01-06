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
    Scanner::Token currentToken;
    Query* currentQuery;

    void consume(TokenType);
    void consumeDataType(std::vector<TokenType>&);
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
    void parseWhereClause(std::string&, Scanner::Token&, TokenType&);
    void parseOrderByClause(std::string&, TokenType&);
    void assureSemiColumn() const;
    void error(const char*) const;
    void deleteQuery();

public:
    Parser(std::istream&);
    Query* parseQuery();
    ~Parser();
};

#endif
