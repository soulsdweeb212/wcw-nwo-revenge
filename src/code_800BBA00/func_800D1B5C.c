/* @header
 * func_800D1B5C
 * VRAM 0x800D1B5C | ROM 0xC4FFC | size 0x34C
 * asm: asm/nonmatchings/code_800BBA00/func_800D1B5C.s
 */
#include "common.h"

extern s32 D_800E3C90[];
extern s32 D_800E3CB0[];
s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void *func_800D6610(void *, s16);
s16 getRingBoundaryPointAlongHeading(void *, s32, void *);

s32 func_800D1B5C(Wrestler *self, Wrestler *other) {
    s16 i;
    s32 mask;
    s32 best;
    s16 bestIdx;
    s32 t;

    if (self->move.flags & 0x1000) {
        mask = 0;
        for (i = 0; i < 4; i++) {
            s16 a1;
            if (i == self->id || i == other->id) {
                continue;
            }
            if (D_800F9D10[i].characterId == -1) {
                continue;
            }
            a1 = D_800F9D10[i].state;
            if (a1 == 0x14) {
                mask |= 1 << D_800F9D10[i].dirIndex;
            }
            if (!(D_800F9D10[i].flags & WR_FLAG_IN_RING)) {
                continue;
            }
            if (a1 == 0xC && (D_800F9D10[i].moveMode & 8)) {
                mask |= 1 << D_800F9D10[i].dirIndex;
            }
            if (!(D_800F9D10[i].flags & 0x100000ULL)) {
                continue;
            }
            if (D_800F9D10[i].moveMode & 0x20) {
                if (D_800F9D10[i].moveMode & 8) {
                    mask |= 1 << D_800F9D10[i].dirIndex;
                }
            }
        }
        best = 0x800;
        for (i = 0; i < 4; i++) {
            t = func_800D3684(D_800E3CB0[i], self->heading);
            t = func_800D3550(t);
            if (best >= t) {
                best = t;
                bestIdx = i;
            }
        }
        if (self->move.flags & 0x20000) {
            bestIdx = (bestIdx + 2) & 3;
        }
        if (((mask & 0xFF) >> bestIdx) & 1) {
            bestIdx = (bestIdx + 1) & 3;
            if (((mask & 0xFF) >> bestIdx) & 1) {
                bestIdx = (bestIdx - 2) & 3;
                if (((mask & 0xFF) >> bestIdx) & 1) {
                    bestIdx = (bestIdx - 1) & 3;
                }
            }
        }
        self->dirIndex = bestIdx;
        other->dirIndex = bestIdx;
        t = (s32)func_800D6610(self, bestIdx);
        if (self->move.flags & 0x20000) {
            t = func_800D35B0(t, 0x800);
        }
        return t;
    }
    {
        s32 sp10[4];
        bestIdx = getRingBoundaryPointAlongHeading(&self->x, self->heading, sp10);
    }
    if (self->move.flags & 0x20000) {
        self->dirIndex = (bestIdx + 2) & 3;
    } else {
        self->dirIndex = bestIdx;
    }
    return D_800E3C90[bestIdx];
}
