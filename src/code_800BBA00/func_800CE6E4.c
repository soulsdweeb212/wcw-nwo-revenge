/* @header
 * func_800CE6E4
 * VRAM 0x800CE6E4 | ROM 0xC1B84 | size 0x64
 * asm: asm/nonmatchings/code_800BBA00/func_800CE6E4.s
 */
#include "common.h"

void translateEntityXZ(void*,void*);
s32 func_800D35B0(s32,s32);
/* Moves w by moveDelta (translateEntityXZ) and turns its heading by turnPerTick
 * each call until stateTimer reaches 6 (then sets the heading to a1 and returns 1). */
s32 func_800CE6E4(Wrestler *w, s32 a1) {
    if (w->stateTimer < 6) {
        translateEntityXZ(w, w->moveDelta);
        w->heading = func_800D35B0(w->heading, w->turnPerTick);
        w->stateTimer++;
        return 0;
    }
    w->heading = a1;
    return 1;
}
