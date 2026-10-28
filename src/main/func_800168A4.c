#include "common.h"

s8 func_80015B84(u8);

/* Parses an envelope level: seeds +0xDD from a random byte and adds the next. */
u8 *func_800168A4(u8 *arg0, u8 *arg1) {
    s8 v = func_80015B84(*arg1++);
    *(s8 *)(arg0 + 0xDD) = v;
    v += *arg1++;
    *(s8 *)(arg0 + 0xDD) = v;
    return arg1;
}

extern f64 D_8003B3F0;
