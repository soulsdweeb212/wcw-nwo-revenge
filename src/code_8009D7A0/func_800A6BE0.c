/* @header
 * func_800A6BE0
 * VRAM 0x800A6BE0 | ROM 0x9A080 | size 0x68
 * asm: asm/nonmatchings/code_8009D7A0/func_800A6BE0.s
 */
#include "common.h"

extern u8 D_8007EF30[];

/* Put the wrestler in a new state: state = actionState, step, stepFlags and pairSignals cleared, flag bits
 * 0x10800000000 and WR_FLAG_RERUN cleared and 0x1000000000 set, then func_800DECAC(w, 0, 0, 0), which only zeroes
 * the slot's D_800F98D0 counter. */
void func_800A6BE0(Wrestler *w, s16 actionState) {
    w->state = actionState;
    w->step = 0;
    w->stepFlags = 0;
    w->pairSignals = 0;
    w->flags = (w->flags & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(w, 0, 0, 0);
}
