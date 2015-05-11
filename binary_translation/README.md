Binary translator
=========================================================================================
Binary translator from my old stack processor in x86 + Nasm assembler and linker for x86.
## Files:
*Nasm assembler and linker files:*

* **asm_opcodes.ods** - it is exel file with opcodes

* **comands_info.txt** - it is text file with opcodes

* **binary_file.h**
* **binary_file.cpp** - it is code for working with binary files

* **map.h**
* **map.cpp** - it is my map library (key - value container) for labels

* **errors.cpp**
* **errors.h**  - it is my library for working with errors (from old project)

* **source_file.cpp**
* **source_file.h** - files for searching opcodes for command and assembling it.

* **assembler.h**
* **assembler.cpp** - it is code for searching labels, assembling file, generating elf


* **hello.txt** - example asm text for compile
* **elf** - example elf, which print 5 times "Hello world!"

*binary translator files:*
* **elf2** - elf, which calculate the factorial of 5 and print x (0x78 = 120 dec - ascii code of 'x')

* **lib_out.txt** - output lib in binary form

* **translator.h**
* **translator.cpp** - add special struct translator - it is a translation unit, bases on asm_commands_table from compiler. translator_table - is a array with translators. 
