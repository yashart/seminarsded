//
// Created by yashart on 19.04.15.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "translator.h"

const int MAX_COMMAND_NAME_LEN = 20;

errors translator_OK(translator* trtor)
{
    if(!trtor)
        return NULL_PTR;
    if(!trtor->initial_command)
        return BAD_FILE;
    if(!trtor->result_table.command)
        return BAD_FILE;
    return OK;
}

errors translator_constructor(translator* trtor)
{
    asm_command_table_constructor(&trtor->result_table);
    trtor->initial_command = (char*) calloc(MAX_COMMAND_NAME_LEN, sizeof(*trtor->initial_command));
    trtor->command_first_operand  = 0;
    trtor->command_second_operand = 0;
    if(translator_OK(trtor))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(translator_OK(trtor));
    return OK;
}

errors translator_destructor(translator* trtor)
{
    if(translator_OK(trtor))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(translator_OK(trtor));
    asm_command_table_destructor(&trtor->result_table);
    free(trtor->initial_command);
    return OK;
}

void translator_dump(translator* trtor)
{
    printf("%s %d %d:\n", trtor->initial_command, trtor->command_first_operand, trtor->command_second_operand);
    asm_command_table_dump(&trtor->result_table);
}

errors translator_add_element(translator* trtor, char* inital_command,\
                              int command_first_operand, int command_second_operand, asm_command_table* result)
{
    strcpy(trtor->initial_command, inital_command);
    trtor->command_first_operand  = command_first_operand;
    trtor->command_second_operand = command_second_operand;
    asm_command_table_copy(&trtor->result_table, result);
    return OK;
}

errors translator_table_OK(translator_table* tr_table)
{
    if(tr_table->quantity_elements < 0)
        return BAD_SIZE;
    for(int i = 0; i < tr_table->quantity_elements; i++)
        if(translator_OK(&tr_table->translator_rules[i]))
            PLEASE_KILL_MY_VERY_BAD_FUNCTION(translator_OK(&tr_table->translator_rules[i]));
    return OK;
}

errors translator_table_constructor(translator_table* tr_table)
{
    tr_table->quantity_elements = 0;
    tr_table->translator_rules = NULL;

    if(translator_table_OK(tr_table))
        return translator_table_OK(tr_table);
    return OK;
}

errors translator_table_destructor(translator_table* tr_table)
{
    if(translator_table_OK(tr_table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(translator_table_OK(tr_table));

    for(int i = 0; i < tr_table->quantity_elements; i++)
    {
        translator_destructor(&tr_table->translator_rules[i]);
    }
    tr_table->quantity_elements = -1;
    free(tr_table->translator_rules);
    return OK;
}

void translator_table_dump(translator_table* tr_table)
{
    for(int i = 0; i < tr_table->quantity_elements; i++)
    {
        translator_dump(&tr_table->translator_rules[i]);
        printf("\n");
    }
}

errors translator_table_add(translator_table* tr_table)
{
    if(translator_table_OK(tr_table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(translator_table_OK(tr_table));

    tr_table->translator_rules = (translator*) realloc(tr_table->translator_rules,\
                                              (tr_table->quantity_elements + 1)*sizeof(*tr_table->translator_rules));
    translator_constructor(&tr_table->translator_rules[tr_table->quantity_elements]);
    tr_table->quantity_elements ++;

    if(translator_table_OK(tr_table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(translator_table_OK(tr_table));
    return OK;
}

errors parse_translator_rules(const char* filename, translator_table* tr_table)
{
    if(translator_table_OK(tr_table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(translator_table_OK(tr_table));

    long rules_len = 0;
    char* rules_str = bin_buffer_scan(filename, &rules_len);
    char* rules_start = rules_str;
    char* commands_tokens = rules_str;
    asm_command rules_command;
    asm_command_constructor(&rules_command);
    char* param1 = (char*) calloc(MAX_COMMAND_NAME_LEN, sizeof(*param1));
    char* param2 = (char*) calloc(MAX_COMMAND_NAME_LEN, sizeof(*param2));
    int operand1 = 0;
    int operand2 = 0;
    while(commands_tokens)
    {
        commands_tokens = strtok(commands_tokens, ";");
        if(commands_tokens != NULL)
            commands_tokens += strlen(commands_tokens) + 1;
        else
            continue;

        translator_table_add(tr_table);
        sscanf(rules_str, "%s %s %s", tr_table->translator_rules[tr_table->quantity_elements - 1].initial_command, \
                        param1, param2);

        tr_table->translator_rules[tr_table->quantity_elements - 1].command_first_operand  = str_to_type(param1);
        tr_table->translator_rules[tr_table->quantity_elements - 1].command_second_operand = str_to_type(param2);
        if(strtok(rules_str, "\n") == NULL)
        {
            rules_str = rules_start + rules_len;
        }else
        {
            rules_str += strlen(rules_str) + 1;
        }
        while(rules_str < commands_tokens)
        {
            sscanf(rules_str ,"%s %s %s %x %d %x %d %c %d+%d %d", rules_command.name, param1, param2, &rules_command.op_code,\
             &rules_command.has_prefix, &rules_command.op_prefix, &rules_command.has_modrm, &rules_command.modrm,\
             &rules_command.add_register, &operand1, &operand2);

            rules_command.param1_t = str_to_type(param1);
            rules_command.param2_t = str_to_type(param2);

            asm_command_table_add(&tr_table->translator_rules[tr_table->quantity_elements - 1].result_table, rules_command);

            if(strtok(rules_str, "\n") == NULL)
            {
                rules_str = rules_start + rules_len;
            }else
            {
                rules_str += strlen(rules_str) + 1;
            }
        }
    }
    asm_command_destructor(&rules_command);
    free(param1);
    free(param2);
    free(rules_start);

    return OK;
}