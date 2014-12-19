#ifndef OPERATOR_TYPE_H
#define OPERATOR_TYPE_H

enum node_type
{
    END_LEXEM,
    NUMBER,
    VARIABLE,
    OPERATOR,
    SEPARATOR,
    COMMAND,
    PRINTF,
    SIMULATOR_DIFFERENCE
};

enum operator_pos
{
    PREFIX,
    INFIX,
    POSTFIX
};

#endif