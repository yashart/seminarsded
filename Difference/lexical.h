#ifndef LEXICAL_H
#define LEXICAL_H

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <malloc.h>
#include "operator_type.h"

struct lexem
{
    int value;
    node_type type;
};


lexem *str_on_tokens(char* str);
int find_number(char** str);
void token_dump(lexem* new_lexem);

#endif