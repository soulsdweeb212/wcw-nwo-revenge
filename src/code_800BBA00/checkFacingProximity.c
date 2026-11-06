/* @header
 * checkFacingProximity  (originally func_800D24C8)
 * VRAM 0x800D24C8 | ROM 0xC5968 | size 0x100
 * asm: asm/nonmatchings/code_800BBA00/checkFacingProximity.s
 */
#include "common.h"

extern f64 D_800E6B08;
extern f64 D_800E6B10;

/* Returns 1 when w is on the floor (WR_FLAG_ON_FLOOR), other is in the ring (WR_FLAG_IN_RING), the angle arg2 is
 * within 0x400 of w->heading, and w's pelvis x and z (jointA[1].x / .z) both lie strictly inside
 * (D_800E6B08, D_800E6B10) = (-320, 320). */
s32 checkFacingProximity(Wrestler *w, Wrestler *other, s32 arg2) {
    f64 f, g;
    if (!(w->flags & WR_FLAG_ON_FLOOR))
        return 0;
    if (!(other->flags & WR_FLAG_IN_RING))
        return 0;
    if (func_800D3550(func_800D3684(arg2, w->heading)) >= 0x400)
        return 0;
    f = w->jointA[1].x;
    if (!(D_800E6B08 < f))
        return 0;
    if (!(f < D_800E6B10))
        return 0;
    g = w->jointA[1].z;
    if (!(D_800E6B08 < g))
        return 0;
    if (g < D_800E6B10)
        return 1;
    return 0;
}
