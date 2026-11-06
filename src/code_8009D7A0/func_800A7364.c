/* @header
 * func_800A7364
 * VRAM 0x800A7364 | ROM 0x9A804 | size 0xB4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7364.s
 */
#include "common.h"

/* Copies the pelvis joint's X/Z (jointA[1]) to the root x/z, then puts the
 * coordinate of the ringSide axis on the apron standing line (+/-265). */
void func_800A7364(Wrestler *w) {
    f32 px = w->jointA[1].x;
    f32 pz = w->jointA[1].z;
    s32 side = w->ringSide;

    w->x = px;
    w->z = pz;
    switch (side) {
    case 0:
        w->z = 265.0f;
        break;
    case 1:
        w->x = 265.0f;
        break;
    case 2:
        w->z = -265.0f;
        break;
    case 3:
        w->x = -265.0f;
        break;
    }
}

s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
