#include "common.h"

extern s32 D_800E3CA0[];   /* heading for each quadrant (0..3) */

/* Snap the entity to the nearest ring boundary: clear its "on-ring" flag, set
 * the quadrant from its current XZ position, copy the position into the ring
 * coordinates, pick the quadrant heading, and clamp the boundary coordinate for
 * the quadrant to +/-265. */
void snapEntityToRingBoundary(u8 *arg0) {
    /* arg0: +0x20 u64 flags, +0x3C s16 quadrant, +0x4C f32 x, +0x54 f32 z,
     *       +0x58 s32 heading, +0x6C f32[3] position */
    *(u64 *)(arg0 + 0x20) &= ~0x10000000ULL;
    *(s16 *)(arg0 + 0x3C) = getXZDirectionQuadrant((f32 *)(arg0 + 0x6C));
    *(f32 *)(arg0 + 0x4C) = *(f32 *)(arg0 + 0x6C);
    *(f32 *)(arg0 + 0x54) = *(f32 *)(arg0 + 0x74);
    *(s32 *)(arg0 + 0x58) = D_800E3CA0[*(s16 *)(arg0 + 0x3C)];
    switch (*(s16 *)(arg0 + 0x3C)) {
    case 0: *(f32 *)(arg0 + 0x54) = 265.0f; break;
    case 1: *(f32 *)(arg0 + 0x4C) = 265.0f; break;
    case 2: *(f32 *)(arg0 + 0x54) = -265.0f; break;
    case 3: *(f32 *)(arg0 + 0x4C) = -265.0f; break;
    }
}
