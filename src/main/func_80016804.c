/* @header
 * func_80016804
 * VRAM 0x80016804 | ROM 0x17404 | size 0x50
 * asm: asm/nonmatchings/main/func_80016804.s
 */
#include "common.h"

s8 func_80015B84(u8);

/* Decode a signed byte into arg0+0xD9, then add the next byte to it. */
u8 *func_80016804(u8 *arg0, u8 *arg1) {
    s8 v = func_80015B84(*arg1++);
    *(s8 *)(arg0 + 0xD9) = v;
    v += *arg1++;
    *(s8 *)(arg0 + 0xD9) = v;
    return arg1;
}

extern f64 D_8003B3F0;
