#ifndef _TOKENTYPE_H
#define _TOKENTYPE_H

enum TokenType
{
    SELECT, CREATE, TABLE, INDEX, PRIMARY, KEY, FROM, INSERT, UPDATE, SET, WHERE, INTO,
    LESS_THAN_OP, LESS_THAN_OR_EQUAL_OP, MORE_THAN_OP, MORE_THAN_OR_EQUAL_OP, EQUAL_OP, NOT_EQUAL_OP,
    WILDCARD, COMMA, SEMI_COLUMN, ORDER, BY, ASC, DESC, ON, COUNT, MAX, MIN, SUM, AVG,
    FIELD_NAME, INT_DATATYPE, DOUBLE_DATATYPE, STRING_DATATYPE, BOOL_DATATYPE,
    OPEN_PARENTHESES, CLOSE_PARENTHESES, STRING, INT, DOUBLE, BOOL, END_OF_FILE, QUIT
};

static const char* tokenTypeToString(TokenType type)
{
    switch (type)
    {
        case SELECT:
            return "SELECT";
        case CREATE:
            return "CREATE";
        case INSERT:
            return "INSERT";
        case UPDATE:
            return "UPDATE";
        case LESS_THAN_OP:
            return "<";
        case LESS_THAN_OR_EQUAL_OP:
            return "<=";
        case MORE_THAN_OP:
            return ">";
        case MORE_THAN_OR_EQUAL_OP:
            return ">=";
        case EQUAL_OP:
            return "=";
        case NOT_EQUAL_OP:
            return "!=";
        case ASC:
            return "ASC";
        case DESC:
            return "DESC";
        case COUNT:
            return "COUNT";
        case MAX:
            return "MAX";
        case MIN:
            return "MIN";
        case SUM:
            return "SUM";
        case AVG:
            return "AVG";
        case FIELD_NAME:
            return "Filed name";
        case INT_DATATYPE:
            return "int";
        case DOUBLE_DATATYPE:
            return "double";
        case BOOL_DATATYPE:
            return "bool";
        case STRING_DATATYPE:
            return "string";
        case INT:
            return "Integer number";
        case DOUBLE:
            return "Floating point number";
        case BOOL:
            return "Boolean value";
        case STRING:
            return "String value";
        case TABLE:
            return "TABLE";
        case INDEX:
            return "INDEX";
        case PRIMARY:
            return "PRIMARY";
        case KEY:
            return "KEY";
        case FROM:
            return "FROM";
        case SET:
            return "SET";
        case WHERE:
            return "WHERE";
        case INTO:
            return "INTO";
        case WILDCARD:
            return "*";
        case COMMA:
            return ",";
        case SEMI_COLUMN:
            return ";";
        case ORDER:
            return "ORDER";
        case BY:
            return "BY";
        case ON:
            return "ON";
        case OPEN_PARENTHESES:
            return "(";
        case CLOSE_PARENTHESES:
            return ")";
        case QUIT:
            return "QUIT";
        case END_OF_FILE:
            return "End of file";
    }

    return "";
}


#endif
