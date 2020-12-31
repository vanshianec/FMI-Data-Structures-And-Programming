#ifndef _PARSER_H
#define _PARSER_H

#include <istream>
#include <vector>
#include "Scanner.h"

class Parser
{
private:
    Scanner scanner;
    Scanner::Token currentToken;
    void consume(TokenType);
    void consumeDataType();
    void consumeColumnValue();
    void consumeOperator();
    void consumeAggregate();
    void parseCreateQuery();
    void parseInsertQuery();
    void parseUpdateQuery();
    void parseSelectQuery();
    void parseCreateTable();
    void parseCreateIndex();
    void parseSelectAggregate(std::vector<std::string>&);
    void parseSelectColumns(std::vector<std::string>&);
    void parseSelectAfterFrom(std::vector<std::string>&);
    void parseWhereClause(std::string&, std::string&);
    void parseOrderByClause(std::string&);
    void assureSemiColumn() const;
    void error(const char *) const;

public:
    Parser(std::istream&);
    void parseQuery();
};

#endif
