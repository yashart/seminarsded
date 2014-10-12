#include "My_calk.h"

errors stackAdd(stack* stk) {
    stackOk(stk);
    stackPush(stk, stackPop(stk) + stackPop(stk));
    stackOk(stk);
}

errors stackSub(stack* stk) {
    stackOk(stk);
    stackData subtrahend = stackPop(stk);
    stackData minuend    = stackPop(stk);
    stackPush(stk, minuend - subtrahend);
    stackOk(stk);
}

errors stackMul(stack* stk) {
    stackOk(stk);
    stackPush(stk, stackPop(stk) * stackPop(stk));
    stackOk(stk);
}

errors stackDel(stack* stk) {
    stackOk(stk);
    stackData divider = stackPop(stk);
    stackData dividend = stackPop(stk);

    stackPush(stk, dividend / divider);
    stackOk(stk);
}