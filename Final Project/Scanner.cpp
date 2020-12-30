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

    char current = input.peek();
    if (std::isdigit(current) || current == '-')
    {
        input.get();
        std::string num;
        num.push_back(current);
        current = input.get();
        bool isDouble = false;
        while (hasMoreTokens() && (std::isdigit(current) || current == '.'))
        {
            if (current == '.')
            {
                isDouble = true;
            }
            num.push_back(current);
            current = input.get();
        }

        result.type = (isDouble ? TokenType::DOUBLE : TokenType::INT);
        result.value = num;
    }
    else if (current == '(')
    {
        result.type = TokenType::OPEN_PARENTHESES;
        input.get();
    }
    else if (current == ')')
    {
        result.type = TokenType::CLOSE_PARENTHESES;
        input.get();
    }
    else if (current == '=')
    {
        result.type = TokenType::EQUAL;
        input.get();
    }
    else if (current == '*')
    {
        result.type = TokenType::WILDCARD;
        input.get();
    }
    else if (current == ';')
    {
        result.type = TokenType::SEMI_COLUMN;
        input.get();
    }
    else if (current == ',')
    {
        result.type = TokenType::COMMA;
        input.get();
    }
    else if (current == '"')
    {
        result.type = TokenType::QUOTES;
    }
    else if (std::isalpha(current) || current == '_')
    {
        std::string word;
        input.get();
        word.push_back(current);
        current = input.get();
        while (hasMoreTokens() && (std::isalpha(current) || current == '_'))
        {
            word.push_back(current);
            current = input.get();
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
        else if (word == "TRUE")
        {
            result.type = TokenType::TRUE;
        }
        else if (word == "FALSE")
        {
            result.type = TokenType::FALSE;
        }
        else if (word == "QUIT")
        {
            result.type = TokenType::QUIT;
        }
        else
        {
            result.type = TokenType::STRING;
            result.value = word;
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
    while (input && input.peek() <= 32)
    {
        input.get();
    }
}

bool Scanner::hasMoreTokens() const
{
    return (bool) input;
}

#endif
