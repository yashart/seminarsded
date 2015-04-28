//
// Created by yashart on 19.04.15.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "translator.h"
#include "assembler.h"

const int MAX_COMMAND_NAME_LEN = 20;
const int PROGRAM_ENTRY_POINT = 0x10054;

errors operands_table_OK(operands_table* operands)
{
    if(!operands)
        return BAD_FILE;
    if((!operands->operand1)&&(operands->quantity_operands != 0))
        return NULL_PTR;
    if((!operands->operand2)&&(operands->quantity_operands != 0))
        return NULL_PTR;
    if(operands->quantity_operands < 0)
        return BAD_SIZE;
    return OK;
}

errors operands_table_constructor(operands_table* operands)
{
    operands->quantity_operands = 0;
    operands->operand1 = NULL;
    operands->operand2 = NULL;

    if(operands_table_OK(operands))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(operands_table_OK(operands));
    return OK;
}

errors operands_table_destructor(operands_table* operands)
{
    if(operands_table_OK(operands))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(operands_table_OK(operands));

    free(operands->operand1);
    free(operands->operand2);
    operands->quantity_operands = -1;
    return OK;
}

void operands_table_dump(operands_table *operands)
{
    printf("\noperands: ");
    for(int i = 0; i < operands->quantity_operands; i++)
        printf("          %d %d\n", operands->operand1[i], operands->operand2[i]);
}

errors operands_table_add(operands_table *operands, int operand1, int operand2)
{
    if(operands_table_OK(operands))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(operands_table_OK(operands));

    operands->operand1 = (int*) realloc(operands->operand1, (operands->quantity_operands + 1) * sizeof(*operands->operand1));
    operands->operand2 = (int*) realloc(operands->operand2, (operands->quantity_operands + 1) * sizeof(*operands->operand2));
    operands->operand1[operands->quantity_operands] = operand1;
    operands->operand2[operands->quantity_operands] = operand2;
    operands->quantity_operands ++;

    if(operands_table_OK(operands))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(operands_table_OK(operands));
    return OK;
}

errors translator_OK(translator* trtor)
{
    if(!trtor)
        return NULL_PTR;
    if(!trtor->initial_command)
        return BAD_FILE;
    if(!trtor->result_table.command)
        return BAD_FILE;
    if(operands_table_OK(&trtor->operands))
        return operands_table_OK(&trtor->operands);
    return OK;
}

errors translator_constructor(translator* trtor)
{
    asm_command_table_constructor(&trtor->result_table);
    operands_table_constructor(&trtor->operands);
    trtor->old_command_opcode = 0;
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
    operands_table_destructor(&trtor->operands);
    asm_command_table_destructor(&trtor->result_table);
    free(trtor->initial_command);
    return OK;
}

void translator_dump(translator* trtor)
{
    printf("%d %s %d %d:\n",trtor->old_command_opcode, trtor->initial_command, trtor->command_first_operand, trtor->command_second_operand);
    asm_command_table_dump(&trtor->result_table);
    operands_table_dump(&trtor->operands);
}

errors translator_add_element(translator *trtor, char old_opcode, char *inital_command, int command_first_operand,
                              int command_second_operand, asm_command_table *result, int operand1, int operand2)
{
    strcpy(trtor->initial_command, inital_command);
    trtor->command_first_operand  = command_first_operand;
    trtor->command_second_operand = command_second_operand;
    asm_command_table_copy(&trtor->result_table, result);
    operands_table_add(&trtor->operands, operand1, operand2);
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
    char* rules_start = del_comments_in_translator_rules(rules_str, &rules_len);
    free(rules_str);
    rules_str = rules_start;
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
        sscanf(rules_str, "%d %s %s %s", &tr_table->translator_rules[tr_table->quantity_elements - 1].old_command_opcode,\
                        tr_table->translator_rules[tr_table->quantity_elements - 1].initial_command, \
                        param1, param2);

        tr_table->translator_rules[tr_table->quantity_elements - 1].command_first_operand  = str_to_param_t(param1);
        tr_table->translator_rules[tr_table->quantity_elements - 1].command_second_operand = str_to_param_t(param2);
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

            rules_command.param1_t = str_to_param_t(param1);
            rules_command.param2_t = str_to_param_t(param2);

            asm_command_table_add(&tr_table->translator_rules[tr_table->quantity_elements - 1].result_table, rules_command);
            operands_table_add(&tr_table->translator_rules[tr_table->quantity_elements - 1].operands, operand1, operand2);

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

char * del_comments_in_translator_rules(char *text, long *text_len)
{
    if(!text)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);

    char* translator_text   = (char*) calloc(*text_len, sizeof(*translator_text));
    char* comments_text     = (char*) calloc(*text_len, sizeof(*translator_text));
    char* text_no_comments  = (char*) calloc(*text_len, sizeof(*translator_text));

    long old_txt_ptr = 0;
    while(*text_len > old_txt_ptr)
    {
        if(text[old_txt_ptr] != '{')
        {
            sscanf(text + old_txt_ptr, "%[^{]%[^}]", translator_text, comments_text);
            old_txt_ptr += strlen(translator_text) + strlen(comments_text) + 2;
            text_no_comments = strcat(text_no_comments, translator_text);
        }
        else
            old_txt_ptr = strpbrk(text + old_txt_ptr, "}") - text + 1;
    }
    *text_len = strlen(text_no_comments) + 1;
    printf("%s", text_no_comments);
    free(translator_text);
    free(comments_text);

    if(!text)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);
    return text_no_comments;
}


errors convert_old_code_in_bin(char *program_txt, binary_buffer *old_program, int program_text_len)
{
    if(!program_txt)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);
    if(binary_buffer_OK(old_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(old_program));

    strtok(program_txt, " \n");
    while(strtok(NULL, " \n"));

    char* program_txt_ptr = program_txt;
    while(program_txt_ptr < program_txt + program_text_len)
    {
        bin_buffer_add_elem(old_program, atoi(program_txt_ptr), 1);
        program_txt_ptr += strlen(program_txt_ptr) + 1;
    }

    if(!program_txt)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);
    if(binary_buffer_OK(old_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(old_program));
    return OK;
}

errors convert_old_code_in_new(binary_buffer *old_program, binary_buffer *new_program, translator_table *tr_table)
{
    if(binary_buffer_OK(old_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(old_program));
    if(binary_buffer_OK(new_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(new_program));
    if(translator_table_OK(tr_table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(translator_table_OK(tr_table));

    int label_ptr = 0;

    char operand1 = 0;
    char operand2 = 0;
    for(int old_buffer_ptr = 0; old_buffer_ptr < old_program->length; old_buffer_ptr++)
    {
        for (int table_quantity = 0; table_quantity < tr_table->quantity_elements; table_quantity++)
        {
            if (old_program->buffer[old_buffer_ptr] == tr_table->translator_rules[table_quantity].old_command_opcode)
            {
                for(int asm_commands_quantity = 0; \
                 asm_commands_quantity < tr_table->translator_rules[table_quantity].result_table.quantity_elements;\
                 asm_commands_quantity++)
                {
                     if((tr_table->translator_rules[table_quantity].result_table.command[asm_commands_quantity].param1_t == DATA)\
                     ||(tr_table->translator_rules[table_quantity].result_table.command[asm_commands_quantity].param1_t == CHARDATA)\
                     ||(tr_table->translator_rules[table_quantity].result_table.command[asm_commands_quantity].param1_t == FAROFFSET)\
                     ||(tr_table->translator_rules[table_quantity].result_table.command[asm_commands_quantity].param1_t == FAR8OFFSET)\
                     ||(tr_table->translator_rules[table_quantity].result_table.command[asm_commands_quantity].param1_t == OFFSET))
                    {
                        if(tr_table->translator_rules[table_quantity].operands.operand1[asm_commands_quantity] != 0xFF)
                        {
                            operand1 = (char) tr_table->translator_rules[table_quantity].operands.operand1[asm_commands_quantity];
                        }
                        else
                        {
                            operand1 = old_program->buffer[old_buffer_ptr + 1];
                            old_buffer_ptr++;
                        }
                    }
                    if((tr_table->translator_rules[table_quantity].result_table.command[asm_commands_quantity].param2_t == DATA)\
                     ||(tr_table->translator_rules[table_quantity].result_table.command[asm_commands_quantity].param2_t == CHARDATA)\
                     ||(tr_table->translator_rules[table_quantity].result_table.command[asm_commands_quantity].param2_t == FAROFFSET)\
                     ||(tr_table->translator_rules[table_quantity].result_table.command[asm_commands_quantity].param2_t == FAR8OFFSET)\
                     ||(tr_table->translator_rules[table_quantity].result_table.command[asm_commands_quantity].param2_t == OFFSET))
                    {
                        if(tr_table->translator_rules[table_quantity].operands.operand2[asm_commands_quantity] != 0xFF)
                        {
                            operand2 = (char) tr_table->translator_rules[table_quantity].operands.operand2[asm_commands_quantity];
                        }
                        else
                        {
                            operand2 = old_program->buffer[old_buffer_ptr + 1];
                            old_buffer_ptr++;
                        }
                    }
                    //printf("PARAM1_T = %d, PARAM2_T = %d", tr_table->translator_rules[table_quantity].operands.operand1[asm_commands_quantity], tr_table->translator_rules[table_quantity].operands.operand2[asm_commands_quantity]);

                    add_asm_command_in_bin_buffer(&tr_table->translator_rules[table_quantity].result_table.command[asm_commands_quantity],\
                                                  &label_ptr, new_program, operand1, operand2);

                }
                break;
            }
        }
    }
    if(binary_buffer_OK(old_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(old_program));
    if(binary_buffer_OK(new_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(new_program));
    if(translator_table_OK(tr_table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(translator_table_OK(tr_table));
    return OK;
}

errors parse_labels_in_old_bin(binary_buffer* old_program, translator_table* tr_table, map_header* mp)
{
    if(binary_buffer_OK(old_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(old_program));
    if(translator_table_OK(tr_table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(translator_table_OK(tr_table));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));

    int label_ptr = 0;
    char str_label[2] = {};
    binary_buffer trash_buffer;
    binary_buffer_constructor(&trash_buffer);

    map_header old_commands_in_new_mp;
    map_header_constructor(&old_commands_in_new_mp);

    for(int command_ptr = 0; command_ptr < old_program->length; command_ptr++)
    {
        for(int rule_ptr = 0; rule_ptr < tr_table->quantity_elements; rule_ptr++)
        {
            if(tr_table->translator_rules[rule_ptr].old_command_opcode == old_program->buffer[command_ptr])
            {
                str_label[0] = (char)command_ptr;
                if(old_program->buffer[command_ptr] == 51)
                {
                    map_header_add_elem(mp, str_label, label_ptr);
                }
                map_header_add_elem(&old_commands_in_new_mp, str_label, label_ptr);

                for(int asm_commands_ptr = 0; asm_commands_ptr < tr_table->translator_rules[rule_ptr].result_table.quantity_elements; asm_commands_ptr++)
                {
                    add_asm_command_in_bin_buffer(&tr_table->translator_rules[rule_ptr].result_table.command[asm_commands_ptr], &label_ptr, &trash_buffer, 0, 0);
                    if((tr_table->translator_rules[rule_ptr].result_table.command[asm_commands_ptr].param1_t == (int) FAROFFSET)\
                    &&(tr_table->translator_rules[rule_ptr].operands.operand1[asm_commands_ptr] == 0xFF))
                    {
                        command_ptr++;
                        map_header_add_elem(mp, str_label, old_program->buffer[command_ptr]);
                    }
                    if((tr_table->translator_rules[rule_ptr].result_table.command[asm_commands_ptr].param1_t == (int) FAR8OFFSET)\
                    &&(tr_table->translator_rules[rule_ptr].operands.operand1[asm_commands_ptr] == 0xFF))
                    {
                        command_ptr++;
                        map_header_add_elem(mp, str_label, old_program->buffer[command_ptr]);
                    }
                }

                if((tr_table->translator_rules[rule_ptr].command_first_operand == (int) DATA)\
                 ||(tr_table->translator_rules[rule_ptr].command_first_operand == (int) CHARDATA)\
                 ||(tr_table->translator_rules[rule_ptr].command_first_operand == (int) OFFSET))
                    command_ptr++;
                if((tr_table->translator_rules[rule_ptr].command_second_operand == (int) DATA)\
                 ||(tr_table->translator_rules[rule_ptr].command_second_operand == (int) CHARDATA)\
                 ||(tr_table->translator_rules[rule_ptr].command_second_operand == (int) OFFSET))
                    command_ptr ++;
                break;
            }
        }
    }

    //map_header_dump(&old_commands_in_new_mp);

    for(int map_ptr = 0; map_ptr < mp->quantity_element; map_ptr++)
    {
        str_label[0] = (char) mp->mp[map_ptr].value;
        mp->mp[map_ptr].value = map_header_search(&old_commands_in_new_mp, str_label);

        for(int old_ptr = 0; old_ptr < old_commands_in_new_mp.quantity_element; old_ptr++)
            if(mp->mp[map_ptr].key[0] == old_commands_in_new_mp.mp[old_ptr].key[0])
            {
                mp->mp[map_ptr].key[0] = (char) old_commands_in_new_mp.mp[old_ptr].value;
                break;
            }
    }


    binary_buffer_destructor(&trash_buffer);
    map_header_destructor(&old_commands_in_new_mp);

    if(binary_buffer_OK(old_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(old_program));
    if(translator_table_OK(tr_table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(translator_table_OK(tr_table));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));
    return OK;
}

errors print_labels_from_old_bin (binary_buffer* new_program, map_header* mp)
{
    if(binary_buffer_OK(new_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(new_program));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));

    for(int map_ptr = 0; map_ptr < mp->quantity_element; map_ptr++)
    {
        #define IF_JMP_OFFSET 6
        switch (new_program->buffer[(int) mp->mp[map_ptr].key[0]])
        {
            case (char)0xE9:
                *(int*)&new_program->buffer[(int) mp->mp[map_ptr].key[0] + 1] = (int)(mp->mp[map_ptr].value - mp->mp[map_ptr].key[0] - 5);//5-sizeof(jmp)
                break;
            case (char)0x5F:
                *(int*)&new_program->buffer[(int) mp->mp[map_ptr].key[0] + IF_JMP_OFFSET] = (int)(mp->mp[map_ptr].value - mp->mp[map_ptr].key[0] - 10);//10-sizeof(ja, jb, jne..)

                break;
            default:
                break;
        }
        #undef IF_JMP_OFFSET
    }
    if(binary_buffer_OK(new_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(new_program));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));
    return OK;
}

errors print_out_call_label (binary_buffer* new_program, map_header* mp)
{
    if(binary_buffer_OK(new_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(new_program));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));

    for(int map_ptr = 0; map_ptr < mp->quantity_element; map_ptr++)
    {
        if((char)new_program->buffer[(int) mp->mp[map_ptr].key[0]] == (char)0xE8)
        {
            if(*(int*)&new_program->buffer[(int) mp->mp[map_ptr].key[0] + 1] == 0)
            {
                *(int *) &new_program->buffer[(int) mp->mp[map_ptr].key[0] + 1] = (int) (new_program->length - mp->mp[map_ptr].key[0] - 5);
            }
            else
            {
                *(int*)&new_program->buffer[(int) mp->mp[map_ptr].key[0] + 1] = (int)(mp->mp[map_ptr].value - mp->mp[map_ptr].key[0] - 5);//5-sizeof(jmp)
            }
        }
    }
    long old_buffer_len = new_program->length;
    long lib_len = 0;
    char* lib_text = bin_buffer_scan("lib_out.txt", &lib_len);
    bin_buffer_add_str(new_program, lib_text, lib_len);
    free(lib_text);
    bin_buffer_add_elem(new_program, 0, 4);
    #define STR_IN_OUT_LIB_OFFSET 4
    #define DATA_SEG_IN_OUT_LIB 34
    //printf("mov: %d  %x\n",old_buffer_len + STR_IN_OUT_LIB_OFFSET,  (new_program->buffer[old_buffer_len + STR_IN_OUT_LIB_OFFSET]));
    *(int*)&(new_program->buffer[old_buffer_len + STR_IN_OUT_LIB_OFFSET]) = old_buffer_len + DATA_SEG_IN_OUT_LIB + PROGRAM_ENTRY_POINT;
    //printf("str: %x\n", old_buffer_len + DATA_SEG_IN_OUT_LIB + PROGRAM_ENTRY_POINT);
    #undef STR_IN_OUT_LIB_OFFSET
    #undef DATA_SEG_IN_OUT_LIB
    if(binary_buffer_OK(new_program))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(new_program));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));
    return OK;
}