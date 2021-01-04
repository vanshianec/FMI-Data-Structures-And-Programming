#ifndef _PARSER_CPP
#define _PARSER_CPP

#include <iostream>
#include <vector>
#include "Parser.h"
#include "CreateIndexQuery.h"
#include "CreateTableQuery.h"
#include "InsertQuery.h"
#include "UpdateQuery.h"
#include "SelectQuery.h"

Parser::Parser(std::istream& input) : scanner(input), currentQuery(nullptr)
{
    currentToken = scanner.nextToken();
}

void Parser::consume(TokenType expectedType)
{
    if (currentToken.type != expectedType)
    {
        //TODO !!!IMPORTANT add which type is expected and which is missing
        throw std::invalid_argument("Unexpected token type");
    }

    currentToken = scanner.nextToken();
}

Query* Parser::parseQuery()
{
    deleteQuery();
    if (currentToken.type == TokenType::SEMI_COLUMN)
    {
        consume(TokenType::SEMI_COLUMN);
    }

    if (currentToken.type != TokenType::QUIT && currentToken.type != TokenType::END_OF_FILE)
    {
        if (currentToken.type == TokenType::CREATE)
        {
            parseCreateQuery();
        }
        else if (currentToken.type == TokenType::INSERT)
        {
            parseInsertQuery();
        }
        else if (currentToken.type == TokenType::UPDATE)
        {
            parseUpdateQuery();
        }
        else if (currentToken.type == TokenType::SELECT)
        {
            parseSelectQuery();
        }
        else
        {
            error("Unexpected query keyword");
        }
    }

    if (currentToken.type == TokenType::QUIT)
    {
        consume(TokenType::QUIT);
        assureSemiColumn();
    }

    return currentQuery;
}

void Parser::consumeDataType()
{
    if (currentToken.type == TokenType::INT_DATATYPE)
    {
        consume(TokenType::INT_DATATYPE);
    }
    else if (currentToken.type == TokenType::DOUBLE_DATATYPE)
    {
        consume(TokenType::DOUBLE_DATATYPE);
    }
    else if (currentToken.type == TokenType::BOOL_DATATYPE)
    {
        consume(TokenType::BOOL_DATATYPE);
    }
    else if (currentToken.type == TokenType::STRING_DATATYPE)
    {
        consume(TokenType::STRING_DATATYPE);
    }
    else
    {
        throw std::invalid_argument("Expected a datatype token!");
    }
}

void Parser::consumeColumnValue()
{
    if (currentToken.type == TokenType::INT)
    {
        consume(TokenType::INT);
    }
    else if (currentToken.type == TokenType::DOUBLE)
    {
        consume(TokenType::DOUBLE);
    }
    else if (currentToken.type == TokenType::TRUE)
    {
        consume(TokenType::TRUE);
    }
    else if (currentToken.type == TokenType::FALSE)
    {
        consume(TokenType::FALSE);
    }
    else if (currentToken.type == TokenType::STRING)
    {
        consume(TokenType::STRING);
    }
    else
    {
        throw std::invalid_argument("Invalid argument datatype!");
    }
}

void Parser::consumeOperator()
{
    if (currentToken.type == TokenType::EQUAL_OP)
    {
        consume(TokenType::EQUAL_OP);
    }
    else if (currentToken.type == TokenType::NOT_EQUAL_OP)
    {
        consume(TokenType::NOT_EQUAL_OP);
    }
    else if (currentToken.type == TokenType::LESS_THAN_OR_EQUAL_OP)
    {
        consume(TokenType::LESS_THAN_OR_EQUAL_OP);
    }
    else if (currentToken.type == TokenType::LESS_THAN_OP)
    {
        consume(TokenType::LESS_THAN_OP);
    }
    else if (currentToken.type == TokenType::MORE_THAN_OP)
    {
        consume(TokenType::MORE_THAN_OP);
    }
    else if (currentToken.type == TokenType::MORE_THAN_OR_EQUAL_OP)
    {
        consume(TokenType::MORE_THAN_OR_EQUAL_OP);
    }
    else
    {
        throw std::invalid_argument("Expected an operator!");
    }
}

void Parser::consumeAggregate()
{
    if (currentToken.type == TokenType::MIN)
    {
        consume(TokenType::MIN);
    }
    else if (currentToken.type == TokenType::MAX)
    {
        consume(TokenType::MAX);
    }
    else if (currentToken.type == TokenType::SUM)
    {
        consume(TokenType::SUM);
    }
    else if (currentToken.type == TokenType::AVG)
    {
        consume(TokenType::AVG);
    }
    else if (currentToken.type == TokenType::COUNT)
    {
        consume(TokenType::COUNT);
    }
    else
    {
        throw std::invalid_argument("Expected an aggregate!");
    }
}

void Parser::parseCreateQuery()
{
    consume(TokenType::CREATE);
    if (currentToken.type == TokenType::TABLE)
    {
        parseCreateTable();
    }
    else if (currentToken.type == TokenType::INDEX)
    {
        parseCreateIndex();
    }
    else
    {
        error("Invalid token after CREATE keyword");
    }
}

void Parser::parseCreateTable()
{
    consume(TokenType::TABLE);
    std::string tableName = currentToken.value;
    consume(FIELD_NAME);
    consume(OPEN_PARENTHESES);
    std::vector<std::string> columnNames;
    std::vector<TokenType> columnTypes;
    while (currentToken.type != TokenType::CLOSE_PARENTHESES)
    {
        columnNames.push_back(currentToken.value);
        consume(TokenType::FIELD_NAME);
        columnTypes.push_back(currentToken.type);
        consumeDataType();

        if (currentToken.type != TokenType::CLOSE_PARENTHESES)
        {
            consume(TokenType::COMMA);
        }
    }

    if (columnNames.empty())
    {
        error("At least one column should be created!");
    }

    consume(TokenType::CLOSE_PARENTHESES);

    std::string primaryColumn;
    if (currentToken.type != TokenType::SEMI_COLUMN)
    {
        consume(TokenType::PRIMARY);
        consume(TokenType::KEY);
        primaryColumn = currentToken.value;
        consume(TokenType::FIELD_NAME);
    }

    assureSemiColumn();
    currentQuery = new CreateTableQuery(tableName, columnNames, columnTypes, primaryColumn);
}

void Parser::parseCreateIndex()
{
    consume(TokenType::INDEX);
    consume(TokenType::ON);
    std::string tableName = currentToken.value;
    consume(TokenType::FIELD_NAME);
    consume(TokenType::OPEN_PARENTHESES);
    std::string columnName = currentToken.value;
    consume(FIELD_NAME);
    consume(TokenType::CLOSE_PARENTHESES);
    assureSemiColumn();
    currentQuery = new CreateIndexQuery(tableName, columnName);
}

void Parser::parseInsertQuery()
{
    consume(TokenType::INSERT);
    consume(TokenType::INTO);
    std::string tableName = currentToken.value;
    consume(TokenType::FIELD_NAME);
    consume(TokenType::OPEN_PARENTHESES);
    std::vector<Scanner::Token> columnValues;
    while (currentToken.type != TokenType::CLOSE_PARENTHESES)
    {
        columnValues.push_back(currentToken);
        consumeColumnValue();

        if (currentToken.type != TokenType::CLOSE_PARENTHESES)
        {
            consume(TokenType::COMMA);
        }
    }

    if (columnValues.empty())
    {
        error("Inserted values don't match the number of columns!");
    }

    consume(TokenType::CLOSE_PARENTHESES);
    assureSemiColumn();
    currentQuery = new InsertQuery(tableName, columnValues);
}

void Parser::parseUpdateQuery()
{
    consume(TokenType::UPDATE);
    std::string tableName = currentToken.value;
    consume(TokenType::FIELD_NAME);
    consume(TokenType::SET);
    std::vector<std::string> columnNames;
    std::vector<std::string> columnValues;
    TokenType op;
    while (currentToken.type != TokenType::WHERE)
    {
        columnNames.push_back(currentToken.value);
        consume(TokenType::FIELD_NAME);
        consume(TokenType::EQUAL_OP);
        columnValues.push_back(currentToken.value);
        consumeColumnValue();
        if (currentToken.type != TokenType::WHERE)
        {
            consume(TokenType::COMMA);
        }
    }

    if (columnNames.empty())
    {
        error("At least one column should be updated!");
    }

    std::string whereColumn;
    std::string whereValue;
    TokenType whereOp;
    parseWhereClause(whereColumn, whereValue, whereOp);
    assureSemiColumn();
    currentQuery = new UpdateQuery(tableName, columnNames, columnValues, whereColumn, whereOp, whereValue);
}

void Parser::parseSelectQuery()
{
    consume(TokenType::SELECT);
    std::vector<std::string> columnNames;
    std::vector<TokenType> aggregates;
    if (currentToken.type == TokenType::WILDCARD)
    {
        columnNames.emplace_back("*");
        consume(TokenType::WILDCARD);
    }
    else if (currentToken.type == TokenType::FIELD_NAME)
    {
        parseSelectColumns(columnNames);
    }
    else
    {
        parseSelectAggregate(columnNames, aggregates);
    }

    if (columnNames.empty())
    {
        error("At least one column should be selected!");
    }

    consume(TokenType::FROM);
    parseSelectAfterFrom(columnNames, aggregates);
}

void Parser::parseSelectColumns(std::vector<std::string>& columnNames)
{
    while (currentToken.type != TokenType::FROM)
    {
        columnNames.push_back(currentToken.value);
        consume(TokenType::FIELD_NAME);

        if (currentToken.type != TokenType::FROM)
        {
            consume(TokenType::COMMA);
        }
    }
}

void Parser::parseSelectAggregate(std::vector<std::string>& columnNames, std::vector<TokenType>& aggregates)
{
    while (currentToken.type != TokenType::FROM)
    {
        aggregates.push_back(currentToken.type);
        consumeAggregate();
        consume(TokenType::OPEN_PARENTHESES);
        columnNames.push_back(currentToken.value);
        consume(TokenType::FIELD_NAME);
        consume(TokenType::CLOSE_PARENTHESES);

        if (currentToken.type != TokenType::FROM)
        {
            consume(TokenType::COMMA);
        }
    }
}

void Parser::parseSelectAfterFrom(std::vector<std::string>& columnNames, std::vector<TokenType>& aggregates)
{
    std::string tableName = currentToken.value;
    consume(TokenType::FIELD_NAME);
    std::string whereColumn;
    TokenType whereOp;
    std::string whereValue;
    std::string orderColumn;
    TokenType orderType;

    if (currentToken.type == TokenType::WHERE)
    {
        parseWhereClause(whereColumn, whereValue, whereOp);
    }
    if (currentToken.type == TokenType::ORDER && aggregates.empty())
    {
        parseOrderByClause(orderColumn, orderType);
    }

    assureSemiColumn();
    currentQuery = new SelectQuery(tableName, columnNames, aggregates,
                                   whereColumn, whereOp, whereValue,
                                   orderColumn, orderType);
}

void Parser::parseWhereClause(std::string& whereColumn, std::string& whereValue, TokenType& whereOp)
{
    consume(TokenType::WHERE);
    whereColumn = currentToken.value;
    consume(TokenType::FIELD_NAME);
    whereOp = currentToken.type;
    consumeOperator();
    whereValue = currentToken.value;
    consumeColumnValue();
}

void Parser::parseOrderByClause(std::string& orderColumn, TokenType& orderType)
{
    consume(TokenType::ORDER);
    consume(TokenType::BY);
    orderColumn = currentToken.value;
    consume(TokenType::FIELD_NAME);
    if (currentToken.type == TokenType::ASC)
    {
        consume(TokenType::ASC);
    }
    else if (currentToken.type == TokenType::DESC)
    {
        consume(TokenType::DESC);
    }
    else
    {
        error("Expected ASC or DESC keyword!");
    }
}

void Parser::error(const char* message) const
{
    throw std::invalid_argument(message);
}

void Parser::assureSemiColumn() const
{
    if (currentToken.type != TokenType::SEMI_COLUMN)
    {
        error("Expected a ';'");
    }
}

void Parser::deleteQuery()
{
    if (currentQuery != nullptr)
    {
        delete currentQuery;
        currentQuery = nullptr;
    }
}

Parser::~Parser()
{
    deleteQuery();
}

#endif

