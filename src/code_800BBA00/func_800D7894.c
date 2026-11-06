/* @header
 * func_800D7894
 * VRAM 0x800D7894 | ROM 0xCAD34 | size 0x60
 * asm: asm/nonmatchings/code_800BBA00/func_800D7894.s
 */
#include "common.h"

s16 func_800D7690(Wrestler *, s32, s32);
s32 func_800D35B0(s32, s32);
void translateEntityXZ(void *, void *);

extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern u8 D_800F9850[];

/* Ticks escapeTimer down by one, and by one more when func_800D7690 mode 1
 * (button mash counter) returns 1 for the buttons arg1; returns 1 when
 * escapeTimer has gone negative (escaped). */
s32 func_800D7894(Wrestler *w, s32 arg1) {
    w->escapeTimer = w->escapeTimer - 1;
    if (func_800D7690(w, arg1 & 0xFFFF, 1) == 1) {
        w->escapeTimer = w->escapeTimer - 1;
    }
    return (u32)w->escapeTimer >> 31;
}
