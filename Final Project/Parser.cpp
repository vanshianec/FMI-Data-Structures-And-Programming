#ifndef _PARSER_CPP
#define _PARSER_CPP

#include <iostream>
#include <vector>
#include "Parser.h"

Parser::Parser(std::istream& input) : scanner(input)
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

void Parser::parseQuery()
{
    while (currentToken.type != TokenType::QUIT)
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
        else if (currentToken.type == TokenType::SEMI_COLUMN)
        {
            consume(TokenType::SEMI_COLUMN);
        }
        else
        {
            error("Unexpected query keyword");
        }
    }

    consume(TokenType::QUIT);
    assureSemiColumn();

    std::cout << "Program finished!";
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

    std::string primaryColumn = "none";
    if (currentToken.type != TokenType::SEMI_COLUMN)
    {
        consume(TokenType::PRIMARY);
        consume(TokenType::KEY);
        primaryColumn = currentToken.value;
        consume(TokenType::FIELD_NAME);
    }

    assureSemiColumn();

    std::cout << "Created table: " << tableName << " columns :";
    for (int i = 0; i < columnNames.size(); i++)
    {
        std::cout << " " << columnNames[i] << ", " << columnTypes[i];
    }
    std::cout << " -> primary column: " << primaryColumn << std::endl;
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
    std::cout << "Created index on " << tableName << ", " << columnName << std::endl;
}

void Parser::parseInsertQuery()
{
    consume(TokenType::INSERT);
    consume(TokenType::INTO);
    std::string tableName = currentToken.value;
    consume(TokenType::FIELD_NAME);
    consume(TokenType::OPEN_PARENTHESES);
    std::vector<std::string> columnValues;
    while (currentToken.type != TokenType::CLOSE_PARENTHESES)
    {
        columnValues.push_back(currentToken.value);
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
    std::cout << "Inserted in table: " << tableName << " values : ";
    for (int i = 0; i < columnValues.size(); i++)
    {
        std::cout << columnValues[i] << " ";
    }
    std::cout << std::endl;
}

void Parser::parseUpdateQuery()
{
    consume(TokenType::UPDATE);
    std::string tableName = currentToken.value;
    consume(TokenType::FIELD_NAME);
    consume(TokenType::SET);
    std::vector<std::string> columnNames;
    std::vector<std::string> columnValues;
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

    std::string key = "none";
    std::string value = "none";
    parseWhereClause(key, value);
    assureSemiColumn();

    std::cout << "Updated a table: " << tableName << " values : ";
    for (int i = 0; i < columnNames.size(); i++)
    {
        std::cout << " " << columnNames[i] << ", " << columnValues[i];
    }
    std::cout << " -> key: " << key << " -> value: " << value << std::endl;
}

void Parser::parseSelectQuery()
{
    consume(TokenType::SELECT);
    std::vector<std::string> columnNames;
    if (currentToken.type == TokenType::WILDCARD)
    {
        consume(TokenType::WILDCARD);
    }
    else if (currentToken.type == TokenType::FIELD_NAME)
    {
        parseSelectColumns(columnNames);
    }
    else
    {
        parseSelectAggregate(columnNames);
    }

    consume(TokenType::FROM);
    parseSelectAfterFrom(columnNames);
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

    if (columnNames.empty())
    {
        error("At least one column should be selected!");
    }
}

void Parser::parseSelectAggregate(std::vector<std::string>& columnNames)
{
    while (currentToken.type != TokenType::FROM)
    {
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

    if (columnNames.empty())
    {
        error("At least one column should be selected!");
    }
}

void Parser::parseSelectAfterFrom(std::vector<std::string>& columnNames)
{
    std::string tableName = currentToken.value;
    consume(TokenType::FIELD_NAME);
    std::string key = "none";
    std::string value = "none";
    std::string orderColumn = "none";

    if (currentToken.type == TokenType::WHERE)
    {
        parseWhereClause(key, value);
    }
    if (currentToken.type == TokenType::ORDER)
    {
        parseOrderByClause(orderColumn);
    }

    assureSemiColumn();
    std::cout << "Selected table: " << tableName << " values : ";
    for (int i = 0; i < columnNames.size(); i++)
    {
        std::cout << " " << columnNames[i];
    }
    std::cout << " -> key: " << key << " -> value: " << value << " -> ordered by: " << orderColumn << std::endl;
}

void Parser::parseWhereClause(std::string& key, std::string& value)
{
    consume(TokenType::WHERE);
    key = currentToken.value;
    consume(TokenType::FIELD_NAME);
    consumeOperator();
    value = currentToken.value;
    consumeColumnValue();
}

void Parser::parseOrderByClause(std::string& orderColumn)
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

void Parser::error(const char *message) const
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

#endif

