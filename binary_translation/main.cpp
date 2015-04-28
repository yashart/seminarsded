#include <stdlib.h>
#include "map.h"
#include "source_file.h"
#include "assembler.h"
#include "translator.h"

int main()
{
    /*
    asm_command_table table;
    asm_command_table_constructor(&table);
    asm_command_table_add_all(&table, "comands_info.txt");

    map_header mp;
    map_header_constructor(&mp);

    long prog_len  = 0;
    char* prog_txt = bin_buffer_scan("hello.txt", &prog_len);


    binary_buffer elf_buffer;
    binary_buffer prog_buffer;
    binary_buffer_constructor(&elf_buffer);
    binary_buffer_constructor(&prog_buffer);

    search_labels(prog_txt, (int)prog_len, &mp, &table);
    assembler_command(prog_txt, (int) prog_len, &mp, &table, &prog_buffer);

    generate_elf(&prog_buffer, &elf_buffer);

    bin_buffer_dump(&elf_buffer, "elf");
    binary_buffer_destructor(&elf_buffer);
    binary_buffer_destructor(&prog_buffer);

    map_header_dump(&mp);
    map_header_destructor(&mp);
    //asm_command_table_dump(&table);
    asm_command_table_destructor(&table);
    free(prog_txt);
*/
    translator_table tr_table;
    translator_table_constructor(&tr_table);
    parse_translator_rules("translator_rules.txt", &tr_table);
    //translator_table_dump(&tr_table);

    binary_buffer old_program;
    binary_buffer_constructor(&old_program);
    binary_buffer new_program;
    binary_buffer_constructor(&new_program);
    map_header labels;
    map_header_constructor(&labels);

    long old_program_len = 0;
    char* old_program_str = bin_buffer_scan("old_asm.txt", &old_program_len);
    convert_old_code_in_bin(old_program_str, &old_program, (int)old_program_len);

    convert_old_code_in_new(&old_program, &new_program, &tr_table);

    parse_labels_in_old_bin(&old_program, &tr_table, &labels);

    print_out_call_label(&new_program, &labels);
    print_labels_from_old_bin(&new_program, &labels);

    binary_buffer elf_buffer;
    binary_buffer_constructor(&elf_buffer);
    generate_elf(&new_program, &elf_buffer);

    bin_buffer_dump(&elf_buffer, "elf2");

    binary_buffer_destructor(&elf_buffer);

    //map_header_dump(&labels);

    bin_buffer_dump(&old_program, "old_prog_bin");
    bin_buffer_dump(&new_program, "new_prog_bin");

    map_header_destructor(&labels);
    binary_buffer_destructor(&old_program);
    binary_buffer_destructor(&new_program);
    free(old_program_str);

    translator_table_destructor(&tr_table);

    return 0;
}