/* @header
 * func_800DF5C4
 * VRAM 0x800DF5C4 | ROM 0xD2A64 | size 0x360
 * asm: asm/nonmatchings/code_800DE9C0/func_800DF5C4.s
 */
#include "common.h"

extern u16 D_800E4000[];
extern u16 D_800E4008[];
s16 findBoundaryQuadrant(void *, s32, s32);
s16 func_800D65D0(void *, u16);
s32 func_800DF924(void *, void *);
s32 func_800E07DC(void *);
void func_800E212C(void *);

/* Boundary reactions of w (returns 1 when an action is started). In the ring, dirIndex =
 * findBoundaryQuadrant(w, NULL, 1); when it is not -1: mask bit 4 with D_800E4000[dirIndex] in val and
 * func_800E07DC(w) (no wrestler with the same dirIndex is in state 0x14 before step 4, 0x0A or 0x18) starts
 * state 0x0A at step 1 if func_800DF924(w, other), else state 0x18 unless flags bit 0x1; mask bit 0x8000 with
 * val & 0xF00 == D_800E4000[dirIndex], other WR_FLAG_IN_RING with flag 0x400000 and profile bit 0x400000 starts
 * 0x66; a4 with the same val test, func_800E07DC and no flags bit 0x1 starts 0x18.
 * On the apron: mask bit 4, func_800DF924(w, other) and val & a5 & D_800E4008[ringSide] clear flag
 * 0x8000000000 (set again when func_800D65D0(w, a5) == 1, with dirIndex = (ringSide - 1) & 3 instead of
 * ringSide) and, when func_800E07DC(w), start state 0x0A at step 1. */
s8 func_800DF5C4(Wrestler *w, Wrestler *other, u16 mask, u16 val, u8 a4, u16 a5) {
    s16 idx;

    if (w->flags & WR_FLAG_IN_RING) {
        idx = findBoundaryQuadrant(w, 0, 1);
        w->dirIndex = idx;
        if ((s16)idx == -1) {
            goto L7F4;
        }
        if ((mask & 4) && (D_800E4000[idx] & val) && (s8)func_800E07DC(w)) {
            if ((s8)func_800DF924(w, other)) {
                goto L8DC;
            }
            if (!(w->flags & 1)) {
                func_800A6C48(w, 0x18);
                return 1;
            }
        }
        if ((mask & 0x8000) && (val & 0xF00) == D_800E4000[w->dirIndex] && (other->flags & WR_FLAG_IN_RING) &&
            (other->flags & 0x400000) && (*(u64 *)(w->profile + 0x38) & 0x400000)) {
            func_800E212C(w);
            func_800A6C48(w, 0x66);
            return 1;
        }
        if (a4 && (val & 0xF00) == D_800E4000[w->dirIndex] && (s8)func_800E07DC(w) && !(w->flags & 1)) {
            func_800E212C(w);
            func_800A6C48(w, 0x18);
            return 1;
        }
    }
L7F4:
    if ((mask & 4) && (w->flags & WR_FLAG_ON_APRON) && (s8)func_800DF924(w, other)) {
        if (val & (a5 & D_800E4008[w->ringSide])) {
            u16 s1v;
            w->flags &= ~0x8000000000ULL;
            s1v = w->ringSide;
            if ((s16)func_800D65D0(w, a5) == 1) {
                w->flags |= 0x8000000000ULL;
                s1v = (s1v - 1) & 3;
            }
            w->dirIndex = s1v;
            if ((s8)func_800E07DC(w)) {
L8DC:
                func_800A6C48(w, 0xA);
                w->step = 1;
                return 1;
            }
        }
    }
    return 0;
}
