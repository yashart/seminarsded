//
// Created by yashart on 30.03.15.
//

#ifndef _BINARY_TRANSLATION_ASSEMBLER_H_
#define _BINARY_TRANSLATION_ASSEMBLER_H_

#include "map.h"
#include "binary_file.h"
#include "errors.h"
#include "source_file.h"

errors search_labels (char *program_text, int program_len, map_header *mp, asm_command_table *table);
errors assembler_command(char *program_text, int program_len, map_header *mp, asm_command_table *table, binary_buffer *bin_buffer);
errors command_print(char *program_text, map_header *mp, asm_command_table *table, binary_buffer *buffer,
                     int *label_ptr, int program_len);

errors generate_elf(binary_buffer *program_buf, binary_buffer *elf_buf);
errors add_asm_command_in_bin_buffer(asm_command *command, int *label_ptr, binary_buffer *program, int operand1,
                                     int operand2);
errors print_operand_in_buffer(param_t param, int operand, binary_buffer *program, int *label_ptr);
#endif //_BINARY_TRANSLATION_ASSEMBLER_H_