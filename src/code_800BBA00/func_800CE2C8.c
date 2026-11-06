/* @header
 * func_800CE2C8
 * VRAM 0x800CE2C8 | ROM 0xC1768 | size 0xC0
 * asm: asm/nonmatchings/code_800BBA00/func_800CE2C8.s
 */
#include "common.h"

void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
s32 func_800D3E40(void *, void *, s32, void *);

/* Steps the 10-tick scripted move set up by func_800CE124. While self->stateTimer is below 10: move self by
 * moveDelta (translateEntityXZ), turn its heading by turnPerTick, run the boundary correction func_800D2C2C
 * (self, opp, second, 4.0f, a4, 0xFFFFE), bump stateTimer and return 0. Once it reaches 10: set the heading to
 * a3's +0xC, place self's root x/z at a3's offset rotated by opp->heading around a4 (func_800D3E40) and
 * return 1. The callers pass D_800EB408/D_800EB40C/D_800EB418 and two 16-byte entries of D_800F9B18. */
s32 func_800CE2C8(Wrestler *self, Wrestler *opp, Wrestler *second, u8 *a3, void *a4) {
    if (self->stateTimer >= 10) {
        self->heading = *(s32 *)(a3 + 0xC);
        func_800D3E40(a4, a3, opp->heading, &self->x);
        return 1;
    }
    translateEntityXZ(self, self->moveDelta);
    self->heading = func_800D35B0(self->heading, self->turnPerTick);
    func_800D2C2C(self, opp, second, 4.0f, a4, 0xFFFFE);
    self->stateTimer++;
    return 0;
}
