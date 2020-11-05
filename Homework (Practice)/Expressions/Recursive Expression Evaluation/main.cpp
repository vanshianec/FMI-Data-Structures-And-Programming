#include <iostream>
#include <stdexcept>
#include "Tokenizer.h"

int apply(char op, int left, int right)
{
    if (op == '+')
    {
        return left + right;
    }
    else if (op == '-')
    {
        return left - right;
    }
    else if (op == '*')
    {
        return left * right;
    }
    else if (op == '/')
    {
        return left / right;
    }

    return 0;
}

int evaluate(Tokenizer& tokenizer)
{
    Tokenizer::Token token = tokenizer.findNext();

    if (token.type == Tokenizer::Token::NUM)
    {
        return token.numericValue;
    }
    else if (token.type == Tokenizer::Token::LEFT_PARENTHESES)
    {
        int left, right;
        char op;

        left = evaluate(tokenizer);

        token = tokenizer.findNext();
        if (token.type != Tokenizer::Token::OPERATOR)
        {
            throw std::invalid_argument("Unexpected token, expected '*', '/', '-', or '+' ");
        }
        op = token.symbol;

        right = evaluate(tokenizer);

        token = tokenizer.findNext();
        if (token.type != Tokenizer::Token::RIGHT_PARENTHESES)
        {
            throw std::invalid_argument("Unexpected token, expected a ')'");
        }
        return apply(op, left, right);
    }
    else
    {
        throw std::invalid_argument("Invalid expression");
    }
}

int main()
{
    Tokenizer tokenizer(std::cin);

    std::cout << evaluate(tokenizer) << std::endl;

    return 0;
}
