//
// Created by yashart on 31.03.15.
//

#ifndef _BINARY_TRANSLATION_SOURCE_FILE_H_
#define _BINARY_TRANSLATION_SOURCE_FILE_H_

#include "errors.h"
#include "binary_file.h"
#include "map.h"

enum param_t
{
    NONE        = 0,
    REGISTER    = 1,
    DATA        = 3,
    RMEMORY     = 4,
    FAROFFSET   = 5,
    FAR8OFFSET  = 6,
    CHARDATA    = 7,
    OFFSET      = 8,
    STRING      = 9
};

enum reg_t
{
    EAX         = 1,
    EBX         = 2,
    ECX         = 3,
    EDX         = 4,
    ESP         = 5,
    EBP         = 6,
    ESI         = 7,
    EDI         = 8,
    NO
};

struct asm_command
{
    char* name;
    param_t param1_t;
    param_t param2_t;
    bool has_prefix;
    int op_prefix;
    int op_code;
    bool has_modrm;
    char modrm;
    bool add_register;
};

errors asm_command_ok               (asm_command* command);
errors asm_command_constructor      (asm_command* command);
errors asm_command_destructor       (asm_command* command);
errors asm_command_copy_constructor (asm_command *command1, asm_command command2);
void   asm_command_dump             (asm_command *command);

asm_command scan_asm_command        (char* text_buffer);
param_t     str_to_param_t          (char* str);
int         asm_command_len         (asm_command* command);

struct asm_command_table
{
    int quantity_elements;
    asm_command* command;
};

errors      asm_command_table_ok          (asm_command_table* table);
errors      asm_command_table_constructor (asm_command_table* table);
errors      asm_command_table_destructor  (asm_command_table* table);
void        asm_command_table_dump        (asm_command_table* table);

errors      asm_command_table_copy        (asm_command_table* first_table, asm_command_table* second_table);
errors      asm_command_table_add         (asm_command_table* table, asm_command command);
errors      asm_command_table_add_all     (asm_command_table* table, const char *file_name);

asm_command *asm_command_search(asm_command_table *table, char *text_buffer);

reg_t       str_to_reg_t                  (char* str);
param_t     str_to_type                   (char* str);
int         reg_to_add_opcode             (reg_t reg);

//TO-DO
int         command_modrm(asm_command *command, char *program_txt);
errors      print_param_t(param_t param, binary_buffer *bin_buffer, char *program_text, \
                                           map_header *mp, int *label_ptr);

#endif //_BINARY_TRANSLATION_SOURCE_FILE_H_
