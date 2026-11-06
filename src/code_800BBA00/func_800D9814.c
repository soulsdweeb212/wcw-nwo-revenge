/* @header
 * func_800D9814
 * VRAM 0x800D9814 | ROM 0xCCCB4 | size 0x130
 * asm: asm/nonmatchings/code_800BBA00/func_800D9814.s
 */
#include "common.h"

extern f64 D_800E6FF0,D_800E6FF8;
/* Returns 1 when the wrestler is in the ring (WR_FLAG_IN_RING) in state 10 with dirIndex 0 (WR_FLAG_TEAM_B set) or 2
 * (clear), or when it is on the apron (WR_FLAG_ON_APRON) with the pelvis (jointA[1].x and .z) both above D_800E6FF0
 * (WR_FLAG_TEAM_B set) or both below D_800E6FF8 (clear); else 0. The caller func_800D9568 calls it without
 * arguments, leaving its own record in a0. */
s32 func_800D9814(Wrestler *w) {
    s16 dir;
    if(w->flags&WR_FLAG_IN_RING) {
        if(w->state==10) {
            if(w->flags&WR_FLAG_TEAM_B) dir=0; else dir=2;
            if(dir==w->dirIndex) return 1;
        }
    }
    if(w->flags&WR_FLAG_ON_APRON) {
        if(w->flags&WR_FLAG_TEAM_B) {
            if(w->jointA[1].x>D_800E6FF0 && w->jointA[1].z>D_800E6FF0) return 1;
        } else {
            if(w->jointA[1].x<D_800E6FF8 && w->jointA[1].z<D_800E6FF8) return 1;
        }
    }
    return 0;
}
