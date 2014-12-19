#include "lexical.h"
#include "differentiation.h"

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
        if(strncmp(str_pos, "while", 5) == 0)
        {
            new_lexem[lexem_length - 1].type  = COMMAND;
            new_lexem[lexem_length - 1].value = *str_pos;
            str_pos += 5;
            continue;
        }
        if(strncmp(str_pos, "int", 3) == 0)
        {
            lexem_length--;
            str_pos += 3;
            continue;
        }
        if(strncmp(str_pos, "if", 2) == 0)
        {
            new_lexem[lexem_length - 1].type  = COMMAND;
            new_lexem[lexem_length - 1].value = *str_pos;
            str_pos += 2;
            continue;
        }
        if(strncmp(str_pos, "printf(\"%d\",", 12) == 0)
        {
            new_lexem[lexem_length - 1].type  = PRINTF;
            str_pos += 12;
            new_lexem[lexem_length - 1].value = *str_pos;
            str_pos += 2;
            continue;
        }

        if(strncmp(str_pos, "==", 2) == 0)
        {
            new_lexem[lexem_length - 1].type = OPERATOR;
            new_lexem[lexem_length - 1].value = 'e';
            str_pos += 2;
            continue;
        }
        if((*str_pos == '=')||(*str_pos == '<')||(*str_pos == '>'))
        {
            new_lexem[lexem_length - 1].type  = OPERATOR;
            new_lexem[lexem_length - 1].value = *str_pos;
            str_pos++;
            continue;
        }
        if('a' <= *str_pos && *str_pos <= 'z')
        {
            new_lexem[lexem_length - 1].type  = VARIABLE;
            new_lexem[lexem_length - 1].value = *str_pos;
            str_pos++;
            continue;
        }
        if((*str_pos == ' ')||(*str_pos == '\n'))
        {
            lexem_length--;
            str_pos ++;
            continue;
        }
        if((*str_pos == '+')||(*str_pos == '-')||(*str_pos == '*')||(*str_pos == '/')
                            ||(*str_pos == '(')||(*str_pos == ')')||(*str_pos == '{')||(*str_pos == '}'))
        {
            if((*str_pos == '}')&&(new_lexem[lexem_length - 2].value == ';')
                    &&(new_lexem[lexem_length - 2].type == SEPARATOR))
                lexem_length--;
            new_lexem[lexem_length - 1].type  = OPERATOR;
            new_lexem[lexem_length - 1].value = *str_pos;
            str_pos++;
            continue;
        }
        if(*str_pos == ';')
        {
            new_lexem[lexem_length - 1].type  = SEPARATOR;
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
