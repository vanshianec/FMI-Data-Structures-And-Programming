#ifndef _SCANNER_CPP
#define _SCANNER_CPP

#include "Scanner.h"

Scanner::Scanner(std::istream& _input) : input(_input) {}

Scanner::Token Scanner::nextToken()
{
    Token result{TokenType::END_OF_FILE};

    skipWhiteSpace();

    if (!hasMoreTokens())
    {
        return result;
    }

    char current = input.get();
    if (std::isdigit(current) || current == '-')
    {
        std::string num;
        if (current == '-' && !hasMoreTokens())
        {
            throw std::invalid_argument("Invalid token");
        }

        num.push_back(current);
        int dotsCount = 0;
        int numLength = 1;
        current = input.peek();
        while (hasMoreTokens() && (std::isdigit(current) || current == '.'))
        {
            if (current == '.')
            {
                dotsCount++;
            }
            num.push_back(current);
            numLength++;
            current = input.get();
        }

        if (dotsCount > 1 || num[numLength - 1] == '.' || (num[0] == '-' && num[1] == '.'))
        {
            throw std::invalid_argument("Invalid number token");
        }

        result.type = (dotsCount == 1 ? TokenType::DOUBLE : TokenType::INT);
        result.value = num;
    }
    else if (current == '(')
    {
        result.type = TokenType::OPEN_PARENTHESES;
    }
    else if (current == ')')
    {
        result.type = TokenType::CLOSE_PARENTHESES;
    }
    else if (current == '*')
    {
        result.type = TokenType::WILDCARD;
    }
    else if (current == ';')
    {
        result.type = TokenType::SEMI_COLUMN;
    }
    else if (current == ',')
    {
        result.type = TokenType::COMMA;
    }
    else if (current == '=')
    {
        result.type = TokenType::EQUAL_OP;
    }
    else if (current == '<')
    {
        if (input.peek() == '=')
        {
            result.type = TokenType::LESS_THAN_OR_EQUAL_OP;
            input.get();
        }
        else
        {
            result.type = TokenType::LESS_THAN_OP;
        }
    }
    else if (current == '>')
    {
        if (input.peek() == '=')
        {
            result.type = TokenType::MORE_THAN_OR_EQUAL_OP;
            input.get();
        }
        else
        {
            result.type = TokenType::MORE_THAN_OP;
        }
    }
    else if (current == '!' && input.peek() == '=')
    {
        result.type = TokenType::NOT_EQUAL_OP;
        input.get();
    }
    else if (current == '"')
    {
        std::string stringValue;
        while (input.peek() != '"' && hasMoreTokens())
        {
            stringValue.push_back(input.get());
        }

        if (!hasMoreTokens())
        {
            throw std::invalid_argument("String value quotes should be closed");
        }

        input.get();
        result.type = TokenType::STRING;
        result.value = stringValue;
    }
    else if (std::isalpha(current) || current == '_')
    {
        std::string word;
        word.push_back(current);
        while (hasMoreTokens() && (std::isalpha(input.peek()) || input.peek() == '_'))
        {
            word.push_back(input.get());
        }

        if (word == "SELECT")
        {
            result.type = TokenType::SELECT;
        }
        else if (word == "SET")
        {
            result.type = TokenType::SET;
        }
        else if (word == "UPDATE")
        {
            result.type = TokenType::UPDATE;
        }
        else if (word == "WHERE")
        {
            result.type = TokenType::WHERE;
        }
        else if (word == "FROM")
        {
            result.type = TokenType::FROM;
        }
        else if (word == "CREATE")
        {
            result.type = TokenType::CREATE;
        }
        else if (word == "PRIMARY")
        {
            result.type = TokenType::PRIMARY;
        }
        else if (word == "INSERT")
        {
            result.type = TokenType::INSERT;
        }
        else if (word == "INTO")
        {
            result.type = TokenType::INTO;
        }
        else if (word == "ORDER")
        {
            result.type = TokenType::ORDER;
        }
        else if (word == "BY")
        {
            result.type = TokenType::BY;
        }
        else if (word == "TABLE")
        {
            result.type = TokenType::TABLE;
        }
        else if (word == "INDEX")
        {
            result.type = TokenType::INDEX;
        }
        else if (word == "ON")
        {
            result.type = TokenType::ON;
        }
        else if (word == "KEY")
        {
            result.type = TokenType::KEY;
        }
        else if (word == "ASC")
        {
            result.type = TokenType::ASC;
        }
        else if (word == "DESC")
        {
            result.type = TokenType::DESC;
        }
        else if (word == "COUNT")
        {
            result.type = TokenType::COUNT;
        }
        else if (word == "MAX")
        {
            result.type = TokenType::MAX;
        }
        else if (word == "MIN")
        {
            result.type = TokenType::MIN;
        }
        else if (word == "AVG")
        {
            result.type = TokenType::AVG;
        }
        else if (word == "SUM")
        {
            result.type = TokenType::SUM;
        }
        else if (word == "string")
        {
            result.type = TokenType::STRING_DATATYPE;
        }
        else if (word == "int")
        {
            result.type = TokenType::INT_DATATYPE;
        }
        else if (word == "double")
        {
            result.type = TokenType::DOUBLE_DATATYPE;
        }
        else if (word == "bool")
        {
            result.type = TokenType::BOOL_DATATYPE;
        }
        else if (word == "TRUE")
        {
            result.type = TokenType::TRUE;
            result.value = "1";
        }
        else if (word == "FALSE")
        {
            result.type = TokenType::FALSE;
            result.value = "0";
        }
        else if (word == "QUIT")
        {
            result.type = TokenType::QUIT;
        }
        else
        {
            result.type = TokenType::FIELD_NAME;
        }
    }
    else
    {
        std::string message = "Invalid character: ";
        message.push_back(current);
        throw std::invalid_argument(message);
    }


    return result;
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

#endif
