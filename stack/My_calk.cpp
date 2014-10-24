#include "My_calk.h"

errors stackAdd(stack* stk) {
    if(!stackOk(stk)) {ASSERT_OK(stk);};
    stackPush(stk, stackPop(stk) + stackPop(stk));
    if(!stackOk(stk)) {ASSERT_OK(stk);};
}

errors stackSub(stack* stk) {
    if(!stackOk(stk)) {ASSERT_OK(stk);};
    stackData subtrahend = stackPop(stk);
    stackData minuend    = stackPop(stk);
    stackPush(stk, minuend - subtrahend);
    if(!stackOk(stk)) {ASSERT_OK(stk);};
}

errors stackMul(stack* stk) {
    if(!stackOk(stk)) {ASSERT_OK(stk);};
    stackPush(stk, stackPop(stk) * stackPop(stk));
    if(!stackOk(stk)) {ASSERT_OK(stk);};
}

errors stackDel(stack* stk) {
    if(!stackOk(stk)) {ASSERT_OK(stk);};
    stackData divider = stackPop(stk);
    stackData dividend = stackPop(stk);

    stackPush(stk, dividend / divider);
    if(!stackOk(stk)) {ASSERT_OK(stk);};
}