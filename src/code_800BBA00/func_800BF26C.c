/* @header
 * func_800BF26C
 * VRAM 0x800BF26C | ROM 0xB270C | size 0x90
 * asm: asm/nonmatchings/code_800BBA00/func_800BF26C.s
 */
#include "common.h"

extern u16 D_800EB4B8[];

/* Decrements the wrestler's counter D_800EB4B8[w->id]; when it goes negative the
 * 0x1000000000000000 flag is cleared (and the counter clamped to 0), otherwise
 * the flag stays set. */
void func_800BF26C(Wrestler *w) {
    u64 *flags = &w->flags;
    u16 v;

    *flags &= ~0x1000000000000000ULL;
    v = D_800EB4B8[w->id] - 1;
    D_800EB4B8[w->id] = v;
    if ((s16)v < 0) {
        D_800EB4B8[w->id] = 0;
        return;
    }
    *flags |= 0x1000000000000000ULL;
}
