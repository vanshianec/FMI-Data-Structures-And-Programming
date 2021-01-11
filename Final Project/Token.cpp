#ifndef _TOKEN_CPP
#define _TOKEN_CPP

#include "Token.h"

void Token::write(std::fstream& out)
{
    out.write((char*) &type, sizeof(TokenType));
    int length = value.length();
    out.write((char*) &length, sizeof(length));
    out.write(value.c_str(), length);
}

void Token::read(std::fstream& in)
{
    in.read((char*) &type, sizeof(TokenType));
    int length;
    in.read((char*) &length, sizeof(length));
    value.resize(length);
    in.read(&value[0], length);
}


#endif
