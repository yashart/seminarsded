#include "map.h"
#include "source_file.h"
#include "assembler.h"

int main()
{
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
    return 0;
}