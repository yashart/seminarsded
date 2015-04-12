#include "errors.h"
#include <stdio.h>
#include <assert.h>

void dump(const errors ERROR, const char* FUNCTION_NAME, const int LINE, const char* FILE, const bool kill)
{
    printf("ERROR!!! %d in %s file in %s line: %d", ERROR, FILE, FUNCTION_NAME, LINE);
    if(kill)
        assert(0);
}