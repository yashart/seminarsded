#include "lexical.h"

lexem *str_on_tokens(char *str)
{
    if(str == NULL)
    {
        errno = EFAULT;
        perror("NULL pointer");
    }
    char* str_pos = str;
    int lexem_length = 0;
    const int MAX_LEXEMS = 50;
    lexem* new_lexem = (lexem*) calloc(MAX_LEXEMS, sizeof(*new_lexem));
    if(new_lexem == NULL)
    {
        errno = EFAULT;
        perror("NULL pointer");
    }
    while(*str_pos != '\0')
    {
        lexem_length++;
        if(new_lexem == NULL)
        {
            errno = EFAULT;
            perror("NULL pointer");
        }

        if((0 <= ((*str_pos) - '0'))&& (((*str_pos) - '0') <= 9))
        {
            new_lexem[lexem_length - 1].type  = NUMBER;
            new_lexem[lexem_length - 1].value = find_number(&str_pos);
            continue;
        }
        if((strncmp(str_pos, "sin", 3) == 0)||(strncmp(str_pos, "cos", 3) == 0))
        {
            new_lexem[lexem_length - 1].type  = OPERATOR;
            new_lexem[lexem_length - 1].value = *str_pos;
            str_pos += 3;
            continue;
        }
        if('a' <= *str_pos && *str_pos <= 'z')
        {
            new_lexem[lexem_length - 1].type  = VARIABLE;
            new_lexem[lexem_length - 1].value = *str_pos;
            str_pos++;
            continue;
        }
        if(*str_pos == ' ')
        {
            lexem_length--;
            str_pos ++;
            continue;
        }
        if((*str_pos == '+')||(*str_pos == '-')||(*str_pos == '*')||(*str_pos == '/')
                            ||(*str_pos == '(')||(*str_pos == ')'))
        {
            new_lexem[lexem_length - 1].type  = OPERATOR;
            new_lexem[lexem_length - 1].value = *str_pos;
            str_pos++;
            continue;
        }
        errno = EINVAL;
        perror("Bad string");
        break;
    }
    new_lexem[lexem_length].type  = END_LEXEM;
    new_lexem[lexem_length].value = 0;
    return new_lexem;
}

int find_number(char **str)
{
    int value = 0;
    while((0 <= ((**str) - '0') ) && (((**str) - '0') <= 9))
    {
        value = value * 10 + (**str) - '0';
        (*str)++;
    }
    return value;
}

void token_dump(lexem *new_lexem)
{
    for(int i = 0; new_lexem[i].type != END_LEXEM; i++)
    {
        if(new_lexem[i].type == NUMBER)
        {
            printf("%d %d\n", new_lexem[i].type, new_lexem[i].value);
        }else
            printf("%d %c\n", new_lexem[i].type, new_lexem[i].value);
    }
}
