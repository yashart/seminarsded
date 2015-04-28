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

struct operands_table
{
    int* operand1;
    int* operand2;
    int quantity_operands;
};

errors operands_table_OK            (operands_table* operands);
errors operands_table_constructor   (operands_table* operands);
errors operands_table_destructor    (operands_table* operands);
void operands_table_dump            (operands_table *operands);

errors operands_table_add           (operands_table *operands, int operand1, int operand2);

struct translator
{
    char old_command_opcode;
    char* initial_command;
    int command_first_operand;
    int command_second_operand;
    asm_command_table result_table;
    operands_table operands;
};

errors translator_OK            (translator* trtor);
errors translator_constructor   (translator* trtor);
errors translator_destructor    (translator* trtor);
void   translator_dump          (translator* trtor);

errors translator_add_element(translator *trtor, char old_opcode, char *inital_command, int command_first_operand,
                              int command_second_operand, asm_command_table *result, int operand1, int operand2);

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

errors parse_translator_rules       (const char *filename, translator_table *tr_table);
char * del_comments_in_translator_rules(char *text, long *text_len);
errors convert_old_code_in_bin      (char *program_txt, binary_buffer *old_program, int program_text_len);
errors convert_old_code_in_new      (binary_buffer *old_program, binary_buffer *new_program, translator_table *tr_table);

errors parse_labels_in_old_bin      (binary_buffer* old_program, translator_table* tr_table, map_header* mp);
errors print_labels_from_old_bin    (binary_buffer* new_program, map_header* mp);
errors print_out_call_label         (binary_buffer* new_program, map_header* mp);

#endif //BINARY_TRANSLATION_TRANSLATOR_H
