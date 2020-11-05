
#ifndef _TOKENIZER_H
#define _TOKENIZER_H

#include <istream>

class Tokenizer
{

public:
    struct Token
    {
        enum Type
        {
            NUM, OPERATOR, LEFT_PARENTHESES, RIGHT_PARENTHESES, ERROR
        };

        Type type;
        int numericValue;
        char symbol;
    };

    Tokenizer(std::istream&);

    Token findNext();
    bool hasNext();
private:

    std::istream& in;
    void clearWhiteSpace();
};

#endif
