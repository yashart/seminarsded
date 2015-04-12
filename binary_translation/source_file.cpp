//
// Created by yashart on 31.03.15.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "source_file.h"
#include "map.h"

const int MAX_COMMAND_NAME_LENGTH = 10;
const int PROGRAM_ENTRY_POINT = 0x10054;
//asm_comand--------------------------------------------
errors asm_command_ok(asm_command* command)
{
    if(!command)
        return BAD_FILE;
    if(!command->name)
        return NULL_PTR;
    return OK;
}
errors asm_command_constructor(asm_command* command)
{
    command->name           = (char*) calloc(MAX_COMMAND_NAME_LENGTH, sizeof(*command->name));
    command->has_prefix     = false;
    command->op_code        = 0;
    command->op_prefix      = 0;
    command->param1_t       = NONE;
    command->param2_t       = NONE;
    command->has_modrm      = false;
    command->modrm          = 0;
    command->add_register   = false;

    if(asm_command_ok(command))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_ok(command));

    return OK;
}
errors asm_command_destructor(asm_command* command)
{
    if(asm_command_ok(command))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_ok(command));

    free(command->name);
    command->name = NULL;
    return OK;
}

errors asm_command_copy_constructor (asm_command *command1, asm_command command2)
{
    if(asm_command_ok(command1))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_ok(command1));

    strcpy(command1->name, command2.name);
    command1->op_code       = command2.op_code;
    command1->modrm         = command2.modrm;
    command1->has_modrm     = command2.has_modrm;
    command1->has_prefix    = command2.has_prefix;
    command1->op_prefix     = command2.op_prefix;
    command1->param1_t      = command2.param1_t;
    command1->param2_t      = command2.param2_t;
    command1->add_register  = command2.add_register;
    if(asm_command_ok(command1))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_ok(command1));

    return OK;
}

void asm_command_dump(asm_command *command)
{
    printf("name: %s; operator1: %d; operator2: %d; opcode: %x; has_prefix: %d; prefix: %x; has_modrm: %d; modrm: %x; add_register: %d\n",
    command->name, command->param1_t, command->param2_t, command->op_code, command->has_prefix, command->op_prefix,
    command->has_modrm, command->modrm, command->add_register);

}

asm_command scan_asm_command(char* text_buffer)
{
    asm_command command;
    asm_command_constructor(&command);

    char operator1[MAX_COMMAND_NAME_LENGTH] = {};
    char operator2[MAX_COMMAND_NAME_LENGTH] = {};

    sscanf(text_buffer ,"%s %s %s %x %d %x %d %c %d", command.name, operator1, operator2, &command.op_code, &command.has_prefix,
    &command.op_prefix, &command.has_modrm, &command.modrm, &command.add_register);

    command.param1_t = str_to_param_t(operator1);
    command.param2_t = str_to_param_t(operator2);

    if(asm_command_ok(&command))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_ok(&command));

    return command;
}

param_t str_to_param_t(char* str)
{
    if(!str)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);

    if(!strcmp(str, "NONE"))
        return NONE;
    if(!strcmp(str, "REGISTER"))
        return REGISTER;
    if(!strcmp(str, "DATA"))
        return DATA;
    if(!strcmp(str, "RMEMORY"))
        return RMEMORY;
    if(!strcmp(str, "FAROFFSET"))
        return FAROFFSET;
    if(!strcmp(str, "FAR8OFFSET"))
        return FAR8OFFSET;
    if(!strcmp(str, "CHARDATA"))
        return CHARDATA;
    if(!strcmp(str, "OFFSET"))
        return OFFSET;
    if(!strcmp(str, "STRING"))
        return STRING;

    PLEASE_DONT_KILL_MY_VERY_BAD_FUNCTION(BAD_FILE);
    return NONE;
}

int asm_command_len(asm_command* command)
{
    int command_len = 0;
    if(command->op_code != 0)
        command_len ++;
    if(command->has_prefix)
        command_len++;
    if(command->has_modrm)
        command_len++;
    return command_len;
}

//asm_comand_table:--------------------------------
errors asm_command_table_ok(asm_command_table* table)
{
    if(!table)
        return BAD_FILE;
    if((!table->command)&&(table->quantity_elements != 0))
        return NULL_PTR;
    if(table->quantity_elements < 0)
        return BAD_SIZE;
    return OK;
}

errors asm_command_table_constructor(asm_command_table* table)
{
    table->quantity_elements = 0;
    table->command = (asm_command*) calloc(0, sizeof(*table->command));

    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));

    return OK;
}

errors asm_command_table_destructor(asm_command_table* table)
{
    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));

    for(int i = 0; i < table->quantity_elements; i++)
    {
        asm_command_destructor(&table->command[i]);
    }

    free(table->command);
    table->command = NULL;
    table->quantity_elements = -17;
    return OK;
}

void asm_command_table_dump(asm_command_table* table)
{
    printf("Command table: %d elements\n", table->quantity_elements);
    for(int i = 0; i < table->quantity_elements; i++)
        asm_command_dump(&table->command[i]);
}

errors asm_command_table_add(asm_command_table* table, asm_command command)
{
    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));

    table->command = (asm_command*) realloc(table->command, (table->quantity_elements+1)*sizeof(*table->command));
    asm_command_constructor(&table->command[table->quantity_elements]);
    asm_command_copy_constructor(&table->command[table->quantity_elements], command);

    table->quantity_elements++;

    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));

    return OK;
}

errors asm_command_table_add_all(asm_command_table* table, const char *file_name)
{
    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));

    asm_command command;

    long buffer_len = 0;
    char* buffer = bin_buffer_scan(file_name, &buffer_len);
    char* string_in_buffer = buffer;

    while(string_in_buffer - buffer < buffer_len)
    {
        command = scan_asm_command(string_in_buffer);
        asm_command_table_add(table, command);
        asm_command_destructor(&command);

        string_in_buffer = strtok(string_in_buffer,"\n");
        string_in_buffer += strlen(string_in_buffer)+1;
    }

    free(buffer);
    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));

    return OK;
}

asm_command *asm_command_search(asm_command_table *table, char *text_buffer)
{
    if(!text_buffer)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);
    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));

    char* str_pointer = text_buffer;
    param_t operator1 = NONE;
    param_t operator2 = NONE;
    for(int i = 0; i < table->quantity_elements; i++)
    {
        if(!strcmp(table->command[i].name, str_pointer))
        {
            if(table->command[i].param1_t != NONE)
                operator1 = str_to_type (str_pointer + strlen(str_pointer) + 1);
            if(table->command[i].param2_t != NONE)
                operator2 = str_to_type (str_pointer + 2 + strlen(str_pointer) + strlen(str_pointer + strlen(str_pointer) + 1));

            printf("%d %d %s %d\n", operator1, operator2, text_buffer, str_pointer + 2 + strlen(str_pointer) + strlen(str_pointer + strlen(str_pointer) + 1));

            if((operator1 == DATA)&&(table->command[i].param1_t == CHARDATA))
                return &table->command[i];

            if((operator1 == NONE)&&((table->command[i].param1_t == FAROFFSET)||(table->command[i].param1_t == FAR8OFFSET)))
                return &table->command[i];

            if((operator1 == table->command[i].param1_t)&&(operator2 == table->command[i].param2_t))
                return &table->command[i];

            if(operator2 == REGISTER)
                if((operator1 == table->command[i].param1_t)&&(RMEMORY == table->command[i].param2_t))
                    return &table->command[i];

            if(operator1 == REGISTER)
                if((RMEMORY == table->command[i].param1_t)&&(operator2 == table->command[i].param2_t))
                    return &table->command[i];

            if(operator1 == REGISTER)
                if((operator1 == table->command[i].param1_t)&&(table->command[i].param2_t == OFFSET))
                    return &table->command[i];
        }
    }

    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));

    return &table->command[0];
}

reg_t str_to_reg_t(char* str)
{
    if(!str)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);

    if(!strcmp(str, "eax"))
        return EAX;
    if(!strcmp(str, "ebx"))
        return EBX;
    if(!strcmp(str, "ecx"))
        return ECX;
    if(!strcmp(str, "edx"))
        return EDX;
    if(!strcmp(str, "ebp"))
        return EBP;
    if(!strcmp(str, "edi"))
        return EDI;
    if(!strcmp(str, "esi"))
        return ESI;
    if(!strcmp(str, "esp"))
        return ESP;

    return NO;
}

param_t str_to_type(char* str)
{
    if(!str)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);
    if(str_to_reg_t(str) != NO)
        return REGISTER;
    if(*str == '[')
        return RMEMORY;
    if(strspn(str, "0123456789") == strlen(str))
        return DATA;
    if(*str == '"')
        return STRING;
    return NONE;
}

int reg_to_add_opcode(reg_t reg)
{
    switch (reg)
    {
        case EAX:
            return 0;
        case ECX:
            return 1;
        case EDX:
            return 2;
        case EBX:
            return 3;
        case ESP:
            return 4;
        case EBP:
            return 5;
        case ESI:
            return 6;
        case EDI:
            return 7;
        default:
            PLEASE_DONT_KILL_MY_VERY_BAD_FUNCTION(BAD_FILE);
    }
    return 0;
}

int command_modrm(asm_command *command, char *program_txt)
{
    if(asm_command_ok(command))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_ok(command));



    if(asm_command_ok(command))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_ok(command));

    return 0xFF;
}

errors print_param_t(param_t param, binary_buffer *bin_buffer, char *program_text, map_header *mp, int *label_ptr)
{
    if(binary_buffer_OK(bin_buffer))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(bin_buffer));
    if(!program_text)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);

    int str_len = 0;
    switch(param)
    {
        case DATA:
            bin_buffer_add_elem(bin_buffer, atoi(program_text), 4);
            *label_ptr += 4;
            break;
        case CHARDATA:
            bin_buffer_add_elem(bin_buffer, atoi(program_text), 1);
            *label_ptr += 1;
            break;
        case FAROFFSET:
            bin_buffer_add_elem(bin_buffer, map_header_search(mp, program_text) - *label_ptr - 4, 4);
            *label_ptr += 4;
            break;
        case FAR8OFFSET:
            bin_buffer_add_elem(bin_buffer, char(map_header_search(mp, program_text) - *label_ptr - 1), 1);
            *label_ptr += 1;
            break;
        case OFFSET:
            bin_buffer_add_elem(bin_buffer, map_header_search(mp, program_text) + PROGRAM_ENTRY_POINT, 4);
            *label_ptr += 4;
            break;
        case STRING:
            str_len = (int)strlen(program_text);
            bin_buffer_add_str(bin_buffer, program_text, str_len);
            *label_ptr += str_len;
            break;
        default:
            break;
    }

    if(binary_buffer_OK(bin_buffer))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(bin_buffer));
    if(!program_text)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);

    return OK;
}