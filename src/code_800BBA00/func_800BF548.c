/* @header
 * func_800BF548
 * VRAM 0x800BF548 | ROM 0xB29E8 | size 0xE4
 * asm: asm/nonmatchings/code_800BBA00/func_800BF548.s
 */
#include "common.h"

extern s16 D_800EB490[];
void func_800BF338(Wrestler *, s8, s32);

/* Per-wrestler tick counter D_800EB490[w->id]. Mode 0 resets it; mode 1
 * increments it and, when it reaches the limit -- 90 when w has flag
 * 0x400000000, else 60, with the amount read from profile byte 2 / byte 1 --
 * resets it and adds that amount to w->health via func_800BF338(w, amount, 1). */
void func_800BF548(Wrestler *w, s16 mode) {
    s32 limit; u8 amount;
    switch (mode) {
    case 0: D_800EB490[w->id] = 0; break;
    case 1:
        D_800EB490[w->id]++;
        if (w->flags & 0x400000000ULL) {
            amount = w->profile[2]; limit = 90;
        } else {
            amount = w->profile[1]; limit = 60;
        }
        if (D_800EB490[w->id] >= limit) {
            D_800EB490[w->id] = 0;
            func_800BF338(w, (s8)amount, 1);
        }
        break;
    }
}
