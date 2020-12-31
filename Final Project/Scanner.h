#ifndef _SCANNER_H
#define _SCANNER_H

#include <istream>
#include "TokenType.h"

class Scanner
{
public:
    struct Token
    {
        TokenType type;
        std::string value;
    };

    Scanner(std::istream&);

    Token nextToken();
    void skipWhiteSpace();
    bool hasMoreTokens() const;

private:
    std::istream& input;
};

#endif
