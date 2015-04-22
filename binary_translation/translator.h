//
// Created by yashart on 19.04.15.
//

//---------------------------------------
//Format file for parsing:
//COMMAND FIRST_OPERAND SECOND_OPERAND
//NAME PARAM1_T PARAM2_T OP_CODE HAS_PREFIX OP_PREFIX HAS_MODRM MODRM ADD_REGISTER+OPERAND1 OPERAND2
//NAME PARAM1_T PARAM2_T OP_CODE HAS_PREFIX OP_PREFIX HAS_MODRM MODRM ADD_REGISTER+OPERAND1 OPERAND2;
//COMMAND FIRST_OPERAND SECOND_OPERAND
//NAME PARAM1_T PARAM2_T OP_CODE HAS_PREFIX OP_PREFIX HAS_MODRM MODRM ADD_REGISTER+OPERAND1 OPERAND2;
//---------------------------------------


#ifndef BINARY_TRANSLATION_TRANSLATOR_H
#define BINARY_TRANSLATION_TRANSLATOR_H

#include "errors.h"
#include "map.h"
#include "binary_file.h"
#include "source_file.h"

struct translator
{
    char* initial_command;
    int command_first_operand;
    int command_second_operand;
    asm_command_table result_table;
};

errors translator_OK            (translator* trtor);
errors translator_constructor   (translator* trtor);
errors translator_destructor    (translator* trtor);
void   translator_dump          (translator* trtor);

errors translator_add_element   (translator* trtor, char* inital_command,\
                                 int command_first_operand, int command_second_operand,asm_command_table* result);

struct translator_table
{
    translator* translator_rules;
    int quantity_elements;
};

errors translator_table_OK          (translator_table* tr_table);
errors translator_table_constructor (translator_table* tr_table);
errors translator_table_destructor  (translator_table* tr_table);
void   translator_table_dump        (translator_table* tr_table);
errors translator_table_add         (translator_table* tr_table);

errors parse_translator_rules(const char *filename, translator_table *tr_table);

#endif //BINARY_TRANSLATION_TRANSLATOR_H
