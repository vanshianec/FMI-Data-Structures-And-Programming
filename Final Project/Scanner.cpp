#ifndef _SCANNER_CPP
#define _SCANNER_CPP

#include "Scanner.h"

Scanner::Scanner(std::istream& _input) : input(_input) {}

Token Scanner::nextToken()
{
    skipWhiteSpace();

    if (!hasMoreTokens())
    {
        return Token{END_OF_FILE};
    }

    char current = input.get();
    switch (current)
    {
        case '(' :
            return Token{TokenType::OPEN_PARENTHESES};
        case ')' :
            return Token{TokenType::CLOSE_PARENTHESES};
        case '*' :
            return Token{TokenType::WILDCARD};
        case ';':
            return Token{TokenType::SEMI_COLUMN};
        case ',':
            return Token{TokenType::COMMA};
        case '=':
            return Token{TokenType::EQUAL_OP};
        case '<':
            return lessThanOperator();
        case '>':
            return moreThanOperator();
        case '!':
            return notEqualOperator();
        case '"':
            return stringValue();
        default:
            if (isNumber(current))
            {
                return numberVariable(current);
            }
            else if (isAlphabeticOrUnderscore(current))
            {
                return stringVariable(current);
            }
            else
            {
                std::string message = "Invalid character: ";
                message.push_back(current);
                throw std::invalid_argument(message);
            }
    }
}

void Scanner::skipWhiteSpace()
{
    while (hasMoreTokens() && input.peek() <= 32)
    {
        input.get();
    }
}

bool Scanner::hasMoreTokens() const
{
    return (bool) input;
}

Token Scanner::lessThanOperator()
{
    if (input.peek() == '=')
    {
        input.get();
        return Token{LESS_THAN_OR_EQUAL_OP};
    }

    return Token{LESS_THAN_OP};
}

Token Scanner::moreThanOperator()
{
    if (input.peek() == '=')
    {
        input.get();
        return Token{MORE_THAN_OR_EQUAL_OP};
    }

    return Token{MORE_THAN_OP};
}

Token Scanner::notEqualOperator()
{
    if (input.peek() != '=')
    {
        throw std::invalid_argument("Invalid token! Expected '=' token after '!'");
    }

    input.get();
    return Token{NOT_EQUAL_OP};
}

Token Scanner::stringValue()
{
    std::string stringValue;
    while (input.peek() != '"' && hasMoreTokens())
    {
        stringValue.push_back(input.get());
    }

    if (!hasMoreTokens())
    {
        throw std::invalid_argument("String quotes should be closed");
    }

    input.get();
    return Token{STRING, stringValue};
}

bool isNumber(char c)
{
    return std::isdigit(c) || c == '-';
}

Token Scanner::numberVariable(char current)
{
    validateNegativeNumber(current);

    std::string num;
    int dotsCount = 0;
    int numLength = 1;
    num.push_back(current);
    while (hasMoreTokens() && (std::isdigit(input.peek()) || isDot(input.peek())))
    {
        current = input.get();
        num.push_back(current);
        numLength++;
        if (isDot(current))
        {
            dotsCount++;
        }
    }

    validateFloatingPointNumber(num, dotsCount, numLength);

    return Token{(dotsCount == 1 ? TokenType::DOUBLE : TokenType::INT), num};
}

void Scanner::validateNegativeNumber(char current) const
{
    if (current == '-' && !hasMoreTokens())
    {
        throw std::invalid_argument("Invalid token");
    }
}

bool isDot(char c)
{
    return c == '.';
}

void validateFloatingPointNumber(const std::string& num, int dotsCount, int numLength)
{
    if (dotsCount > 1 || num[numLength - 1] == '.' || (num[0] == '-' && num[1] == '.'))
    {
        throw std::invalid_argument("Invalid number token");
    }
}

bool isAlphabeticOrUnderscore(char c)
{
    return c == '_' || std::isalpha(c);
}

Token Scanner::stringVariable(char current)
{
    std::string word;
    word.push_back(current);
    while (hasMoreTokens() && (isAlphabeticOrUnderscore(input.peek())))
    {
        word.push_back(input.get());
    }

    if (word == "SELECT")
    {
        return Token{SELECT};
    }
    else if (word == "SET")
    {
        return Token{SET};
    }
    else if (word == "UPDATE")
    {
        return Token{UPDATE};
    }
    else if (word == "WHERE")
    {
        return Token{WHERE};
    }
    else if (word == "FROM")
    {
        return Token{FROM};
    }
    else if (word == "CREATE")
    {
        return Token{CREATE};
    }
    else if (word == "PRIMARY")
    {
        return Token{PRIMARY};
    }
    else if (word == "INSERT")
    {
        return Token{INSERT};
    }
    else if (word == "INTO")
    {
        return Token{INTO};
    }
    else if (word == "ORDER")
    {
        return Token{ORDER};
    }
    else if (word == "BY")
    {
        return Token{BY};
    }
    else if (word == "TABLE")
    {
        return Token{TABLE};
    }
    else if (word == "INDEX")
    {
        return Token{INDEX};
    }
    else if (word == "ON")
    {
        return Token{ON};
    }
    else if (word == "KEY")
    {
        return Token{KEY};
    }
    else if (word == "ASC")
    {
        return Token{ASC};
    }
    else if (word == "DESC")
    {
        return Token{DESC};
    }
    else if (word == "COUNT")
    {
        return Token{COUNT};
    }
    else if (word == "MAX")
    {
        return Token{MAX};
    }
    else if (word == "MIN")
    {
        return Token{MIN};
    }
    else if (word == "AVG")
    {
        return Token{AVG};
    }
    else if (word == "SUM")
    {
        return Token{SUM};
    }
    else if (word == "string")
    {
        return Token{STRING_DATATYPE};
    }
    else if (word == "int")
    {
        return Token{INT_DATATYPE};
    }
    else if (word == "double")
    {
        return Token{DOUBLE_DATATYPE};
    }
    else if (word == "bool")
    {
        return Token{BOOL_DATATYPE};
    }
    else if (word == "TRUE")
    {
        return Token{BOOL, "1"};
    }
    else if (word == "FALSE")
    {
        return Token{BOOL, "0"};
    }
    else if (word == "QUIT")
    {
        return Token{QUIT};
    }
    else
    {
        return Token{FIELD_NAME, word};
    }
}

#endif
