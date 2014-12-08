#include "differentiation.h"

int main()
{
    node* main_node = NULL;
    char* string = "(x+3)*x";
    lexem* lex = str_on_tokens(string);
    token_dump(lex);
    printf("\n");
    main_node = get_G0(lex);
    node_dump(main_node);
    printf("\n");
    main_node = difference(main_node);
    node_dump(main_node);
    node_destructor(main_node);
    return 0;
}