#ifndef _TOKEN_H
#define _TOKEN_H

#include "TokenType.h"
#include <string>
#include <fstream>

struct Token
{
    TokenType type;
    std::string value;

    void write(std::fstream&);
    void read(std::fstream&);
};

#endif
