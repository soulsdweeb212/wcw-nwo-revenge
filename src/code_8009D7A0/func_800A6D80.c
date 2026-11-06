/* @header
 * func_800A6D80
 * VRAM 0x800A6D80 | ROM 0x9A220 | size 0xC4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A6D80.s
 */
#include "common.h"


/* Put the wrestler in state `state`: clear step, stepFlags and pairSignals, clear flag mask 0x10800000000 |
 * WR_FLAG_RERUN and set 0x1000000000, call func_800DECAC(w, 0, 0, 0) (zeroes the slot's D_800F98D0 counter),
 * clear WR_FLAG_PAIR_LEADER, empty both attached[] slots (-1) and set WR_FLAG_RERUN. */
void func_800A6D80(Wrestler *w, s16 state) {
    w->state = state;
    w->step = 0;
    w->stepFlags = 0;
    w->pairSignals = 0;
    w->flags = (w->flags & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(w, 0, 0, 0);
    w->flags &= ~WR_FLAG_PAIR_LEADER;
    w->attached[0] = -1;
    w->attached[1] = -1;
    w->flags |= WR_FLAG_RERUN;
}
