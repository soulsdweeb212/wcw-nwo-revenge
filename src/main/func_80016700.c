#include "common.h"

u8 *func_80016700(u8 *arg0, u8 *arg1) {
    u8 v = *arg1;
    arg0[0xF2] = 0;
    arg0[0xF3] = v;
    return arg1 + 1;
}
