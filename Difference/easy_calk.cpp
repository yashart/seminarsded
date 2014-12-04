#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

/*
G0 ::= E
E ::= T {'+', T}*
T ::= P {'*'P}*
P ::= "("E ")"|N

*/
const int MAX_STR_LENGTH = 30;
char* str = NULL;
char* str_pointer = NULL;

int GetG0();
int GetE();
int GetMul();
int GetBrack();
int GetN();

int main()
{
    GetG0();
    return 0;
}

int GetG0()
{
    str = (char*) calloc(MAX_STR_LENGTH, sizeof(*str));
    str_pointer = str;
    if(!str_pointer)
    {
        errno = EFAULT;
        perror("NULL pointer");
    }
    scanf("%s", str);
    int val = GetE();
    if(*str_pointer != 0)
    {
        printf("Plak-Plak\n");
    }
    printf("%d", val);


    free(str);
    return val;
}

int GetN()
{
    if(!((0 <= (*str_pointer - '0'))&&((*str_pointer - '0') <= 9)))
    {
        errno = EINVAL;
        perror("Bad string");
    }
    int val = 0;
    while((0 <= (*str_pointer - '0'))&&((*str_pointer - '0') <= 9))
    {
        val = val * 10 + (*str_pointer - '0');
        str_pointer++;
    }
    return val;
}

int GetBrack()
{
    if(*str_pointer == '(')
    {
        str_pointer++;
        int val = GetE();
        if(*str_pointer != ')')
        {
            errno = EINVAL;
            perror("Bad Bracket");
        }
        str_pointer++;
        return val;
    }
    return GetN();
}

int GetMul()
{
    int val = GetBrack();
    if(*str_pointer == '*')
    {
        str_pointer++;
        val *= GetBrack();
    }
    return val;

}

int GetE()
{
    int val = GetMul();
    while((*str_pointer == '+')||(*str_pointer == '-'))
    {
        if (*str_pointer == '+')
        {
            str_pointer++;
            val += GetMul();
        }
        if (*str_pointer == '-')
        {
            str_pointer++;
            val -= GetMul();
        }
    }
    return val;
}