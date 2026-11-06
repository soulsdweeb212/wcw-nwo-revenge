/* @header
 * func_800A9128
 * VRAM 0x800A9128 | ROM 0x9C5C8 | size 0xE0
 * asm: asm/nonmatchings/code_8009D7A0/func_800A9128.s
 */
#include "common.h"

/* Ring-boundary clamp: when flag bit 0x0800000000000000 is set, move the root (x, z) to the pelvis
 * (jointA[1].x/.z) and pin the axis of the ring side (ringSide) to +/-265 (the apron standing line):
 * side 0 z = +265, 1 x = +265, 2 z = -265, 3 x = -265. Returns 1 when applied, otherwise 0. */
s32 func_800A9128(Wrestler *w) {
    if (w->flags & 0x0800000000000000ULL) {
        f32 x = w->jointA[1].x;
        f32 z = w->jointA[1].z;
        s32 side = w->ringSide;
        w->x = x;
        w->z = z;
        switch (side) {
        case 0: w->z = 265.0f; break;
        case 1: w->x = 265.0f; break;
        case 2: w->z = -265.0f; break;
        case 3: w->x = -265.0f; break;
        }
        return 1;
    }
    return 0;
}
