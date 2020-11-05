
#include "Tokenizer.h"

Tokenizer::Tokenizer(std::istream& _in) : in(_in) {}

Tokenizer::Token Tokenizer::findNext()
{
    clearWhiteSpace();

    Token result = Token{Token::Type::ERROR, -1, '\0'};

    char c = in.peek();

    if (std::isdigit(c))
    {
        result.type = Token::Type::NUM;
        in >> result.numericValue;
    }
    else if (c == '(')
    {
        result.type = Token::Type::LEFT_PARENTHESES;
        in >> result.symbol;
    }
    else if (c == ')')
    {
        result.type = Token::Type::RIGHT_PARENTHESES;
        in >> result.symbol;
    }
    else if (c == '*' || c == '/' || c == '+' || c == '-')
    {
        result.type = Token::Type::OPERATOR;
        in >> result.symbol;
    }
    else
    {
        result.type = Token::Type::ERROR;
        in >> result.symbol;
    }

    return result;
}

void Tokenizer::clearWhiteSpace()
{
    while (in && in.peek() <= 32)
    {
        in.get();
    }
}

bool Tokenizer::hasNext()
{
    return (bool) in;
}