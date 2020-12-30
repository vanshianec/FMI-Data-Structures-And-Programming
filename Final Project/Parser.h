#ifndef _PARSER_H
#define _PARSER_H

#include <istream>
#include "Scanner.h"

class Parser
{
private:
    Scanner scanner;
    Scanner::Token currentToken;

public:
    Parser(std::istream&);
    void parseQuery();
};

#endif
