#include "common.h"

/* Decode a three-byte loop envelope into +0xF8/+0xEE/+0xEF. */
u8 *func_800166B0(u8 *arg0, u8 *arg1) {
    arg0[0xF8] = *arg1++;
    arg0[0xEE] = *arg1++;
    arg0[0xEF] = *arg1;
    return arg1 + 1;
}
