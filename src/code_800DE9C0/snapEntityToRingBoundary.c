/* @header
 * snapEntityToRingBoundary  (originally func_800E08C8)
 * VRAM 0x800E08C8 | ROM 0xD3D68 | size 0x114
 * asm: asm/nonmatchings/code_800DE9C0/snapEntityToRingBoundary.s
 */
#include "common.h"

extern s32 D_800E3CA0[];   /* heading for each ring side (0..3) */

/* Snap the wrestler to the apron line of the nearest ring side: clear the rerun flag, take the ring side from the
 * pelvis position (jointA[1]), move the root there, face the side's heading, and clamp the side's coordinate to
 * +/-265 (the apron standing line). */
void snapEntityToRingBoundary(Wrestler *w) {
    w->flags &= ~WR_FLAG_RERUN;
    w->ringSide = getXZDirectionQuadrant(&w->jointA[1].x);
    w->x = w->jointA[1].x;
    w->z = w->jointA[1].z;
    w->heading = D_800E3CA0[w->ringSide];
    switch (w->ringSide) {
    case 0: w->z = 265.0f; break;
    case 1: w->x = 265.0f; break;
    case 2: w->z = -265.0f; break;
    case 3: w->x = -265.0f; break;
    }
}
