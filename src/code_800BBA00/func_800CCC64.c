/* @header
 * func_800CCC64
 * VRAM 0x800CCC64 | ROM 0xC0104 | size 0x1E4
 * asm: asm/nonmatchings/code_800BBA00/func_800CCC64.s
 */
#include "common.h"

/* Collision push-apart: pick a cardinal direction from the larger of the two
 * entity's X/Z offsets, nudge both entities 2.5 units along it, then (if
 * requested) rotate both entities' facing by the signed amount in flags. */
f32 func_800D3564(f32);
s32 func_800D35B0(s32, s32);
s32 func_800D3B24(void *, void *, s32, f32 *);
s32 func_800D3E40(void *, f32 *, s32, f32 *);
void translateEntityXZ(void *, void *);

void func_800CCC64(u8 *self, u8 *other, u32 flags) {
    f32 offset[3];
    f32 xOff;
    f32 zOff;
    s16 dir;
    s32 rot;
    u8 *selfVec;

    xOff = func_800D3564(*(f32 *)(self + 0x4C));
    zOff = func_800D3564(*(f32 *)(self + 0x54));
    if (zOff <= xOff) {
        dir = 1;
        if (*(f32 *)(self + 0x4C) < 0.0f) {
            dir = 3;
        }
    } else {
        dir = 0;
        if (*(f32 *)(self + 0x54) < 0.0f) {
            dir = 2;
        }
    }
    offset[2] = 0.0f;
    offset[0] = 0.0f;
    switch (dir) {
    case 0:
        offset[2] = 2.5f;
        break;
    case 1:
        offset[0] = 2.5f;
        break;
    case 2:
        offset[2] = -2.5f;
        break;
    case 3:
        offset[0] = -2.5f;
        break;
    }
    translateEntityXZ(self, offset);
    translateEntityXZ(other, offset);
    rot = -((flags & 0x100) != 0) & 0xB;
    if (flags & 0x200) {
        rot = -0xB;
    }
    if (rot != 0) {
        *(s32 *)(self + 0x58) = func_800D35B0(*(s32 *)(self + 0x58), rot);
        *(s32 *)(other + 0x58) = func_800D35B0(*(s32 *)(other + 0x58), rot);
        selfVec = other + 0x4C;
        func_800D3B24(selfVec, self + 0x4C, 0, offset);
        func_800D3E40(selfVec, offset, rot, offset);
        *(f32 *)(self + 0x4C) = offset[0];
        *(f32 *)(self + 0x54) = offset[2];
    }
}
