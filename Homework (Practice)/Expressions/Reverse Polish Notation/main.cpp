#include <iostream>
#include "Tokenizer.h"
#include <stack>
#include <sstream>

int priority(char c)
{
    if (c == '*' || c == '/')
    {
        return 2;
    }
    else if (c == '+' || c == '-')
    {
        return 1;
    }

    return -1;
}

std::string convertToReversePolishNotation(Tokenizer& tokenizer)
{
    std::stringstream result;
    Tokenizer::Token token = tokenizer.findNext();
    std::stack<Tokenizer::Token> s;

    while (token.type != Tokenizer::Token::ERROR)
    {
        if (token.type == Tokenizer::Token::NUM)
        {
            result << token.numericValue << " ";
        }
        else if (token.type == Tokenizer::Token::LEFT_PARENTHESES)
        {
            s.push(token);
        }
        else if (token.type == Tokenizer::Token::RIGHT_PARENTHESES)
        {
            while (!s.empty() && token.type != Tokenizer::Token::LEFT_PARENTHESES)
            {
                result << s.top().symbol << " ";
                s.pop();
            }

            if (s.empty())
            {
                throw std::invalid_argument("invalid expression");
            }
            s.pop();
        }
        else if (token.type == Tokenizer::Token::OPERATOR)
        {
            while (!s.empty() && s.top().type == Tokenizer::Token::OPERATOR
                   && priority(s.top().symbol) >= priority(token.symbol))
            {
                result << s.top().symbol << " ";
                s.pop();
            }
            s.push(token);
        }
        else
        {
            throw std::invalid_argument("invalid expression");
        }

        token = tokenizer.findNext();
    }

    while (!s.empty())
    {
        result << s.top().symbol << " ";
        s.pop();
    }

    return result.str();

}

int main()
{

    Tokenizer tokenizer(std::cin);
    std::cout << convertToReversePolishNotation(tokenizer) << std::endl;

    return 0;
}
