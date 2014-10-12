//{=================================================================================
//!         @file    My_stack.h
//!         @date    2014 - 2015 year
//!         @author  Yashukhin Artem
//!
//!         Example of work calculator and stack
//!
//}=================================================================================


#ifndef myStack
#define myStack

#include <malloc.h>
#include <assert.h>

#define ASSERT_OK(cond) if(cond){stackDump(cond);assert(!"Stack_failed");};
//! change typedef to make stack with other types
//! @warning ! if you change type, stackDump can not work.
typedef int stackData;
//! special type for diagnosis program
enum errors
{
    OK = (int) 'KO',
    NULLPOINTER = (int) 'RTP0',
    ENDOFARRAY = (int) 'ADNE',

};
//! definition of stack. Stack have data, position of last element and maximum of quantity elements. Stack resize, if it is necessary.
struct stack
{
    stackData *data;
    int posEndElem;
    int maxLength;
};
//! check stack on nul pointer, overflow and output abroad
int stackOk(stack *stk);
//! print all information about stack
void stackDump(stack *stk);
//! set stack in first condition, like as constrictor in c++
errors stackConstructor(stack *stk);
//! put an element to the top of the stack
errors stackPush(stack *stk, stackData value);
//! get element from the top of the stack and delete it
stackData stackPop(stack *stk);
//! convert stack in non working condition
errors stackDestruct(stack *stk);

#endif