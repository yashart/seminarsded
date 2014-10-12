//{=================================================================================
//!         @file    main.cpp
//!         @date    2014 - 2015 year
//!         @author  Yashukhin Artem
//!
//!         Example of work calculator and stack
//!
//}=================================================================================

#include "My_calk.h"

int main()
{
    stack st = {};

    stackConstructor(&st);

    stackPush(&st, 15);
    stackDump(&st);

    stackPush(&st, 5);
    stackDump(&st);

    stackDel(&st);
    stackDump(&st);

    stackPush(&st, 5);
    stackDump(&st);

    stackPush(&st, 20);
    stackDump(&st);

    stackMul(&st);

    stackDump(&st);
    stackSub(&st);

    stackDump(&st);

    stackPush(&st, 50);
    stackDump(&st);

    stackAdd(&st);
    stackDump(&st);

    stackDestruct(&st);
    return 0;
}