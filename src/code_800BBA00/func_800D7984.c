/* @header
 * func_800D7984
 * VRAM 0x800D7984 | ROM 0xCAE24 | size 0xA8
 * asm: asm/nonmatchings/code_800BBA00/func_800D7984.s
 */
#include "common.h"

s16 func_800D7690(Wrestler *, s32, s32);
s32 func_800D4198(s32);

/* Ticks escapeTimer down by one, by one more when func_800D7690 mode 1 (button
 * mash counter) returns 1 for the buttons arg1, and back up by one when the
 * random test func_800D4198(0x2EE) passes. When escapeTimer is <= 0 it returns
 * 1, unless arg2 is set, which holds escapeTimer at 0 and returns 0. */
s32 func_800D7984(Wrestler *w, s32 arg1, s32 arg2) {
    w->escapeTimer = w->escapeTimer - 1;
    if (func_800D7690(w, arg1 & 0xFFFF, 1) == 1) {
        w->escapeTimer = w->escapeTimer - 1;
    }
    if ((func_800D4198(0x2EE) << 24) != 0) {
        w->escapeTimer = w->escapeTimer + 1;
    }
    if (w->escapeTimer <= 0) {
        if (arg2 << 24) {
            w->escapeTimer = 0;
        } else {
            return 1;
        }
    }
    return 0;
}
