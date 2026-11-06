/* @header
 * func_800D8D74
 * VRAM 0x800D8D74 | ROM 0xCC214 | size 0x7C
 * asm: asm/nonmatchings/code_800BBA00/func_800D8D74.s
 */
#include "common.h"

s16 func_800D7690(void *, s32, s32);
s32 func_800D35B0(s32, s32);
void translateEntityXZ(Wrestler *, void *);

extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern u8 D_800F9850[];

/* Plays back the movement func_800D7E80 set up.  While w->stateTimer > 0, moves w
 * (and `other`, when given) by w->moveDelta in XZ (root and joints, through
 * translateEntityXZ) and turns w->heading by w->turnPerTick (wrapped).  Then
 * decrements stateTimer; returns 1 when it has run out (new value <= 0). */
s32 func_800D8D74(Wrestler *w, Wrestler *other) {
    u16 v;

    if (w->stateTimer > 0) {
        translateEntityXZ(w, w->moveDelta);
        if (other != 0) {
            translateEntityXZ(other, w->moveDelta);
        }
        w->heading = func_800D35B0(w->heading, w->turnPerTick);
    }
    v = w->stateTimer - 1;
    w->stateTimer = v;
    return (v << 16) < 1;
}
