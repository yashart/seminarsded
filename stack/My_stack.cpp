#include "My_stack.h"
errors STACK_ERRNO = OK;
int stackOk(stack *stk)
{
    if(!(stk->data)) {STACK_ERRNO = NULLPOINTER; return 0;}
    if((0 > stk->posEndElem) || (stk->posEndElem >= stk->maxLength)) {STACK_ERRNO = ENDOFARRAY; return 0;}

    return 1;
}

void stackDump(stack const *stk)
{
    if(STACK_ERRNO != OK)
    {
        printf("WARNING!!! Can't realloc memory! Function wasn't work\n");
    }
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
    stk->data = (stackData*) calloc(INITIAL_STACK_SIZE, sizeof (*(stk->data)));
    stk->posEndElem = 0;
    stk->maxLength = INITIAL_STACK_SIZE;

    if(!stackOk(stk)) {ASSERT_OK(stk);};
    return OK;
}

errors stackPush(stack *stk, stackData const value)
{
    if(!stackOk(stk)) {ASSERT_OK(stk);};

    stackData* checkStackFULL = NULL;
    checkStackFULL = (stackData*) realloc(stk->data, (stk->maxLength * 2) * sizeof (*(stk->data)));
    if(checkStackFULL == NULL)
    {
        STACK_ERRNO = STACKFULL;
        stackDump(stk);
        return STACKFULL;
    }

    stk->data[stk->posEndElem] = value;
    stk->posEndElem++;
    if(stk->posEndElem == stk->maxLength)
    {
        stk->maxLength *= 2;
        stk->maxLength *= 2;
        stk->data = checkStackFULL;
    }
    if(!stackOk(stk)) {ASSERT_OK(stk);};
    return OK;
}

stackData stackPop(stack *stk)
{
    if(!stackOk(stk)) {ASSERT_OK(stk);};

    if(stk->posEndElem == 0)
    {
        STACK_ERRNO = STACKNULLSIZE;
        stackDump(stk);
        return STACKNULLSIZE;
    }


    stk->posEndElem--;

    if((2 * stk->posEndElem < stk->maxLength)&&(stk->maxLength > INITIAL_STACK_SIZE))
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