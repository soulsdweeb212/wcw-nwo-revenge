/* @header
 * func_800996B0
 * VRAM 0x800996B0 | ROM 0x45E20 | size 0x54
 * asm: asm/nonmatchings/code_80090000/func_800996B0.s
 */
#include "common.h"

s32 func_80099734(s32);
s32 func_800B75D4(s32 *, s32, s32);

/* Append an entry described by (func_80099734(arg1), arg2) to the display list in
 * *arg0, updating *arg0 and returning the helper's result. */
s32 func_800996B0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 cur;
    s32 ret;

    cur = *arg0;
    ret = func_800B75D4(&cur, func_80099734(arg1), arg2);
    *arg0 = cur;
    return ret;
}
