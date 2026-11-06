/* @header
 * func_800A6C48
 * VRAM 0x800A6C48 | ROM 0x9A0E8 | size 0x94
 * asm: asm/nonmatchings/code_8009D7A0/func_800A6C48.s
 */
#include "common.h"

extern u8 D_8007EF30[];

/* Like func_800A6BE0 (new state, step/stepFlags/pairSignals cleared, flag bits swapped, func_800DECAC(w, 0, 0, 0))
 * but also raises WR_FLAG_RERUN so the new state's handler runs again this tick. */
void func_800A6C48(Wrestler *w, s32 state) {
    w->state = state;
    w->step = 0;
    w->stepFlags = 0;
    w->pairSignals = 0;
    w->flags = (w->flags & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(w, 0, 0, 0);
    w->flags |= WR_FLAG_RERUN;
}
