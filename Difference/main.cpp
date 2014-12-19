#include "differentiation.h"
#include "fileworking.h"

FILE* TEXT_LATEXT;
FILE* PROGRAM_TEXT;
node* init_node;

int main()
{

    TEXT_LATEXT = fopen("LATEX.txt", "a");
    PROGRAM_TEXT = fopen("PROGRAM.txt", "w");
    node* main_node = NULL;
    char* string = NULL;
    long len = 0;
    read_file("SOURCE.txt", &string, &len);
    //char* string = "a = 0;\nb = 1;\nc = 2;\nd = 5;\nif(a>b)\nif(a>c)\nd = a;\nif(b>a)\nif(b>c)\nd = b;\nif(c>a)\nif(c>b)\nd = c;\na = 0";
    lexem* lex = str_on_tokens(string);
    token_dump(lex);
    printf("\n");
    main_node = get_G0(lex);
    free(lex);
    init_node = main_node;
    int label = 0;
    node_dump_program(init_node, &label);
    fprintf(PROGRAM_TEXT, "\nend");
    /*
    fprintf(TEXT_LATEXT, "$");
    node_dump_formul(main_node);
    fprintf(TEXT_LATEXT, "$\\\\\n");
    init_node = difference(init_node);
    node_dump(init_node);
    simplification(&init_node);
    fprintf(TEXT_LATEXT, "$");
    node_dump_formul(init_node);
    fprintf(TEXT_LATEXT, "$\\\\\n");
    */
    fclose(TEXT_LATEXT);
    fclose(PROGRAM_TEXT);
    free(string);
    node_destructor(main_node);
    //node_destructor(init_node);
    return 0;
}
