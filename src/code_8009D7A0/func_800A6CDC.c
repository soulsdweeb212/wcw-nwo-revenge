/* @header
 * func_800A6CDC
 * VRAM 0x800A6CDC | ROM 0x9A17C | size 0xA4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A6CDC.s
 */
#include "common.h"

extern u8 D_8007EF30[];

/* Put the wrestler in state `action`: clears step, stepFlags and pairSignals, replaces the flag bits
 * 0x10800000000 | WR_FLAG_RERUN with 0x1000000000, calls func_800DECAC(w, 0, 0, 0) (zeroes the slot's
 * D_800F98D0 counter), then empties both
 * attached[] slots (-1) and clears WR_FLAG_PAIR_LEADER. */
void func_800A6CDC(Wrestler *w, s16 action) {
    w->state = action;
    w->step = 0;
    w->stepFlags = 0;
    w->pairSignals = 0;
    w->flags = (w->flags & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(w, 0, 0, 0);
    w->attached[0] = -1;
    w->attached[1] = -1;
    w->flags &= ~WR_FLAG_PAIR_LEADER;
}
