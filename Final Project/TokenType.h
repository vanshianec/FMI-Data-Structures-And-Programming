#ifndef _TOKENTYPE_H
#define _TOKENTYPE_H

enum TokenType
{
    SELECT, CREATE, TABLE, INDEX, PRIMARY, KEY, FROM, INSERT, UPDATE, SET, WHERE, INTO,
    LESS_THAN_OP, LESS_THAN_OR_EQUAL_OP, MORE_THAN_OP, MORE_THAN_OR_EQUAL_OP, EQUAL_OP, NOT_EQUAL_OP,
    WILDCARD, COMMA, SEMI_COLUMN, ORDER, BY, ASC, DESC, ON, COUNT, MAX, MIN, SUM, AVG,
    FIELD_NAME, INT_DATATYPE, DOUBLE_DATATYPE, STRING_DATATYPE, BOOL_DATATYPE,
    OPEN_PARENTHESES, CLOSE_PARENTHESES, STRING, INT, DOUBLE, TRUE, FALSE, END_OF_FILE, QUIT
};

#endif