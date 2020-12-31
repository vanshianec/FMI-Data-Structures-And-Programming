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
    bool isNumber(char) const;
    bool isDot(char) const;
    bool isAlphabeticOrUnderscore(char) const;
    Token lessThanOperator();
    Token moreThanOperator();
    Token notEqualOperator();
    Token stringValue();
    Token stringVariable(char);
    Token numberVariable(char);
    void validateNegativeNumber(char) const;
    void validateFloatingPointNumber(const std::string&, int, int) const;
};

#endif
