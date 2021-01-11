#ifndef _SCANNER_H
#define _SCANNER_H

#include <istream>
#include "Token.h"

class Scanner
{
public:

    Scanner(std::istream&);

    Token nextToken();
    void skipWhiteSpace();
    bool hasMoreTokens() const;

private:
    std::istream& input;

    Token lessThanOperator();
    Token moreThanOperator();
    Token notEqualOperator();
    Token stringValue();
    Token stringVariable(char);
    Token numberVariable(char);
    void validateNegativeNumber(char) const;

};

bool isAlphabeticOrUnderscore(char);
void validateFloatingPointNumber(const std::string&, int, int);
bool isNumber(char);
bool isDot(char);


#endif
