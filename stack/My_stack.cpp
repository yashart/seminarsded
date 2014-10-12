#include "My_stack.h"

errors STACK_ERRNO = OK;

int stackOk(stack *stk)
{
    if(!(stk->data)) {STACK_ERRNO = NULLPOINTER; return 0;}
    if((0 > stk->posEndElem) || (stk->posEndElem >= stk->maxLength)) {STACK_ERRNO = ENDOFARRAY; return 0;}

    return 1;
}

void stackDump(stack *stk)
{

    printf("stack (%s)\n", (char*)&STACK_ERRNO);
    printf("{count = %d\n", stk->posEndElem);
    printf(" data(%d) [%d] max %d\n", sizeof*(stk->data), stk->data, stk->maxLength);
    printf("   {\n");
    for(int i = 0; i < stk->maxLength; i++)
    {
        printf("    [%d] = %d%c\n", i, stk->data[i], (i < stk->posEndElem)?'*':' ');
    }
    printf("   }\n");
    printf("}\n");
}

errors stackConstructor(stack *stk)
{
    stk->data = (stackData*) calloc(10, sizeof (*(stk->data)));
    stk->posEndElem = 0;
    stk->maxLength = 10;

    if(!stackOk(stk)) {ASSERT_OK(stk);};
    return OK;
}

errors stackPush(stack *stk, stackData value)
{
    if(!stackOk(stk)) {ASSERT_OK(stk);};

    stk->data[stk->posEndElem] = value;
    stk->posEndElem++;
    if(stk->posEndElem == stk->maxLength)
    {
        stk->maxLength *= 2;
        stk->data = (stackData*) realloc(stk->data, stk->maxLength * sizeof (*(stk->data)));
    }

    if(!stackOk(stk)) {ASSERT_OK(stk);};
    return OK;
}

stackData stackPop(stack *stk)
{
    if(!stackOk(stk)) {ASSERT_OK(stk);};

    stk->posEndElem--;

    if((2 * stk->posEndElem < stk->maxLength)&&(stk->maxLength > 10))
    {
        stk->maxLength /= 2;
        stk->data = (stackData*) realloc(stk->data, stk->maxLength * sizeof (*(stk->data)));
    }

    if(!stackOk(stk)) {ASSERT_OK(stk);};
    return stk->data[stk->posEndElem];
}

errors stackDestruct(stack *stk)
{
    if(!stackOk(stk)) {ASSERT_OK(stk);};

    free(stk->data);
    stk = NULL;
    return OK;
}