/* @header
 * func_800E1560
 * VRAM 0x800E1560 | ROM 0xD4A00 | size 0xD4
 * asm: asm/nonmatchings/code_800DE9C0/func_800E1560.s
 */
#include "common.h"

extern u16 D_800F98D8[];
void func_800D427C(Wrestler *, s16, s32);

/* Start animation a2 on w with func_800D427C(w, a2, 1); for some values of
 * D_800F98D8[w->id] (within 0xF2D..0xF3E) animation id 0xF30, 0xF31 or 0xF32
 * is used instead. Then turnPerTick = func_800D3684(targetHeading, heading)
 * (signed angle difference) / anim.frameCount, so the turn ends with the
 * animation. */
void func_800E1560(Wrestler *w, s32 targetHeading, s32 a2) {
    s32 idx;

    idx = (s16)(D_800F98D8[w->id] - 0xF2D);
    if ((u32)idx < 18) {
        switch (idx) {
        case 0: case 6: case 14: case 15: case 16: case 17: a2 = 0xF30; break;
        case 1: case 7: a2 = 0xF31; break;
        case 2: case 8: a2 = 0xF32; break;
        default:
            break;
        }
    }
    func_800D427C(w, (s16)a2, 1);
    w->turnPerTick = func_800D3684(targetHeading, w->heading) / w->anim.frameCount;
}
