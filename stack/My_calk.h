//{=================================================================================
//!         @file    My_calk.h
//!         @date    2014 - 2015 year
//!         @author  Yashukhin Artem
//!
//!        My calculator, which uses stack.
//!
//}=================================================================================

#ifndef myCalk
#define myCalk

#include "My_stack.h"
//! basic arithmetic functions

errors stackAdd(stack* stk);

errors stackSub(stack* stk);

errors stackMul(stack* stk);

errors stackDel(stack* stk);


#endif