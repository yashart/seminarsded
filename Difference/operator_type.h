#ifndef OPERATOR_TYPE_H
#define OPERATOR_TYPE_H

enum node_type
{
    END_LEXEM,
    NUMBER,
    VARIABLE,
    OPERATOR
};

enum operator_pos
{
    PREFIX,
    INFIX,
    POSTFIX
};

#endif