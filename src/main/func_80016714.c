#include "common.h"

u8 *func_80016714(u8 *arg0, u8 *arg1) {
    u8 v = *arg1;
    arg0[0xDE] = 0xFF;
    arg0[0xDD] = v >> 1;
    return arg1 + 1;
}
