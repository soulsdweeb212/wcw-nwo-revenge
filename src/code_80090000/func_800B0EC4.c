/* @header
 * func_800B0EC4
 * VRAM 0x800B0EC4 | ROM 0x5D634 | size 0x44
 * asm: asm/nonmatchings/code_80090000/func_800B0EC4.s
 */
#include "common.h"

extern u8 D_8007EF30[];
s32 func_8002B710(void);

s32 func_800B0EC4(void) {
    s32 v = func_8002B710();
    s32 r;
    if (v) {
        r = -((D_8007EF30[0x14C] >> (v - 1)) & 1);
    } else {
        r = -1;
    }
    return r;
}
