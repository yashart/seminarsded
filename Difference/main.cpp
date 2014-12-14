#include "differentiation.h"
FILE* TEXT_LATEXT;
node* init_node;
int main()
{
    TEXT_LATEXT = fopen("LATEX.txt", "a");
    node* main_node = NULL;
    char* string = "x*(x-4)/(300*x+1/(1+1/(x*x+5*(x)/cos(x+4))))";
    lexem* lex = str_on_tokens(string);
    token_dump(lex);
    printf("\n");
    main_node = get_G0(lex);
    free(lex);
    init_node = main_node;
    fprintf(TEXT_LATEXT, "$");
    node_dump_formul(main_node);
    fprintf(TEXT_LATEXT, "$\\\\\n");
    init_node = difference(init_node);
    node_dump(init_node);
    simplification(&init_node);
    fprintf(TEXT_LATEXT, "$");
    node_dump_formul(init_node);
    fprintf(TEXT_LATEXT, "$\\\\\n");
    fclose(TEXT_LATEXT);
    node_destructor(main_node);
    node_destructor(init_node);
    return 0;
}
