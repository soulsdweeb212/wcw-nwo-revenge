/* @header
 * func_800D23B4
 * VRAM 0x800D23B4 | ROM 0xC5854 | size 0x114
 * asm: asm/nonmatchings/code_800BBA00/func_800D23B4.s
 */
#include "common.h"

s8 checkFacingProximity(void *,void *,s32);
void func_800D427C(void *,s32,s32);
extern f64 D_800E6AF8,D_800E6B00;
/* When w is on the floor (WR_FLAG_ON_FLOOR), tests the direction result arg2: if
 * checkFacingProximity(w, other, arg2->angle) passes and arg2->y is below D_800E6AF8 it starts animation 0xEA2
 * and clears w->grappleCtx, returning 1. If instead other is on the apron (WR_FLAG_ON_APRON) and arg2->y is below
 * D_800E6B00 it starts animation 0xE84 and returns 1. Otherwise 0. */
s32 func_800D23B4(Wrestler *w,Wrestler *other,Nw2DirectionResult *arg2) {
    if(w->flags&WR_FLAG_ON_FLOOR) {
        if(checkFacingProximity(w,other,arg2->angle) && (f64)arg2->y < D_800E6AF8) {
            func_800D427C(w,0xEA2,3); w->grappleCtx=0; return 1;
        }
        if(other->flags&WR_FLAG_ON_APRON) {
            if((f64)arg2->y < D_800E6B00) {func_800D427C(w,0xE84,3); return 1;}
        }
    }
    return 0;
}
