//
// Created by yashart on 30.03.15.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "assembler.h"

const int TEXT_ENTER = 8048080;

errors search_labels(char *program_text, int program_len, map_header *mp, asm_command_table *table)
{
    if(!program_text)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);
    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));

    char* str_pointer = program_text;
    //bysicle:
    for(int i = 0; i < program_len; i++)
    {
        if((str_pointer[i] == ' ')||(str_pointer[i] == '\n'))
            str_pointer[i] = 0;
    }
    str_pointer = program_text;
    int label_value = 0;
    asm_command* command = NULL;
    while((str_pointer - program_text) < program_len)
    {
        if(str_pointer[strlen(str_pointer) - 1] == ':')
        {
            map_header_add_elem(mp, str_pointer, label_value);
            str_pointer += strlen(str_pointer) + 1;
            continue;
        }
        command = asm_command_search(table, str_pointer);
        label_value += asm_command_len(command);
        str_pointer += strlen(str_pointer) + 1;
        if(command -> param1_t == NONE)
            continue;
        if(command -> param2_t == NONE)
        {
            str_pointer += strlen(str_pointer) + 1;
            if((command -> param1_t == DATA)||(command -> param1_t == FAROFFSET))
                label_value += 4;
            if((command -> param1_t  == FAR8OFFSET)||(command -> param1_t  == CHARDATA))
                label_value += 1;
            if(command -> param1_t  == STRING)
                label_value += strlen(str_pointer);
            continue;
        }

        if((str_to_reg_t(str_pointer) == NO)||(str_to_reg_t(str_pointer + strlen (str_pointer)) == NO))
            label_value += 4;

        str_pointer += strlen(str_pointer) + 2 + strlen(str_pointer + strlen (str_pointer) + 1);
    }

    if(!program_text)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);
    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));

    return OK;
}

errors assembler_command(char *program_text, int program_len, map_header *mp, asm_command_table *table, binary_buffer *bin_buffer)
{
    if(!program_text)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);
    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));

    int label_value         = 0;
    char* str_pointer       = program_text;

    asm_command* command    = NULL;
    while((str_pointer - program_text) < program_len)
    {
        if(str_pointer[strlen(str_pointer) - 1] == ':')
        {
            str_pointer += strlen(str_pointer) + 1;
            continue;
        }
        command_print(str_pointer, mp, table, bin_buffer, &label_value, program_len);
        command = asm_command_search(table, str_pointer);

        str_pointer += strlen(str_pointer) + 1;
        if(command->param1_t != NONE)
            str_pointer += strlen(str_pointer) + 1;
        if(command->param2_t != NONE)
            str_pointer += strlen(str_pointer) + 1;
    }

    if(!program_text)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);
    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));

    return OK;
}

errors command_print(char *program_text, map_header *mp, asm_command_table *table, binary_buffer *buffer,
                     int *label_ptr, int program_len)
{
    if(!program_text)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);
    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));
    if(binary_buffer_OK(buffer))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(buffer));

    asm_command* command = asm_command_search(table, program_text);
    if(command->has_prefix)
    {
        bin_buffer_add_elem(buffer, command->op_prefix, 1);
        *label_ptr += 1;
    }
    if(command->add_register)
    {
        //if(command->param1_t == REGISTER) - always
        bin_buffer_add_elem(buffer, command->op_code + reg_to_add_opcode(\
                            str_to_reg_t(program_text + strlen(program_text) + 1)) , 1);
        *label_ptr += 1;
    }else
        if(command->op_code != 0)
        {
            bin_buffer_add_elem(buffer, command->op_code, 1);
            *label_ptr += 1;
        }

    if(command->has_modrm)
    {
        bin_buffer_add_elem(buffer, command_modrm(command, program_text), 1);
        *label_ptr += 1;
    }
    print_param_t(command->param1_t, buffer, program_text + strlen(program_text) + 1, mp, label_ptr);
    print_param_t(command->param2_t, buffer,\
                  program_text + strlen(program_text) + 2 + strlen(program_text + strlen(program_text) + 1),\
                  mp, label_ptr);

    if(!program_text)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(NULL_PTR);
    if(asm_command_table_ok(table))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(asm_command_table_ok(table));
    if(map_header_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp));
    if(binary_buffer_OK(buffer))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(buffer));

    return OK;
}

errors generate_elf(binary_buffer *program_buf, binary_buffer *elf_buf)
{
    if(binary_buffer_OK(program_buf))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(program_buf));
    if(binary_buffer_OK(elf_buf))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(elf_buf));

    //ELF Header:
    bin_buffer_add_elem(elf_buf, 0x7F, 1);
    bin_buffer_add_str(elf_buf, "ELF", 3);
    bin_buffer_add_elem(elf_buf, 0, 4);
    bin_buffer_add_elem(elf_buf, 0, 4);
    bin_buffer_add_elem(elf_buf, 0, 4);
    bin_buffer_add_elem(elf_buf, 2, 2);
    bin_buffer_add_elem(elf_buf, 3, 2);
    bin_buffer_add_elem(elf_buf, 0, 4);
    bin_buffer_add_elem(elf_buf, 0x00010054, 4);//entry
    bin_buffer_add_elem(elf_buf, 0x00000034, 4);
    bin_buffer_add_elem(elf_buf, 0, 4);
    bin_buffer_add_elem(elf_buf, 0, 4);
    bin_buffer_add_elem(elf_buf, 0, 2);
    bin_buffer_add_elem(elf_buf, 0x0020, 2);
    bin_buffer_add_elem(elf_buf, 1, 2);
    bin_buffer_add_elem(elf_buf, 0, 2);
    bin_buffer_add_elem(elf_buf, 0, 2);
    bin_buffer_add_elem(elf_buf, 0, 2);
    //Program header
    bin_buffer_add_elem(elf_buf, 1, 4);
    bin_buffer_add_elem(elf_buf, 0, 4);
    bin_buffer_add_elem(elf_buf, 0x00010000, 4);
    bin_buffer_add_elem(elf_buf, 0, 4);
    long filesize = elf_buf->length + 4*4 + program_buf->length;
    bin_buffer_add_elem(elf_buf, filesize, 4);
    bin_buffer_add_elem(elf_buf, filesize, 4);
    bin_buffer_add_elem(elf_buf, 5, 4);
    bin_buffer_add_elem(elf_buf, 0, 4);

    bin_buffer_add_str(elf_buf, program_buf->buffer, program_buf->length);

    if(binary_buffer_OK(program_buf))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(program_buf));
    if(binary_buffer_OK(elf_buf))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(elf_buf));
    return OK;
}
