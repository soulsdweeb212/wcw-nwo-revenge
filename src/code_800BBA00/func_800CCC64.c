/* @header
 * func_800CCC64
 * VRAM 0x800CCC64 | ROM 0xC0104 | size 0x1E4
 * asm: asm/nonmatchings/code_800BBA00/func_800CCC64.s
 */
#include "common.h"

/* Collision push: pick a cardinal direction from the larger of |self->x| and
 * |self->z| (away from the ring centre), move both wrestlers 2.5 units along it,
 * then, when flags has 0x100 (+0xB) or 0x200 (-0xB), turn both headings by that
 * amount and swing self's x/z around other's root position by the same angle. */
f32 func_800D3564(f32);
s32 func_800D35B0(s32, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D3B24 */
s32 func_800D3B24(void *, void *, s32, f32 *);
#endif
s32 func_800D3E40(void *, f32 *, s32, f32 *);
void translateEntityXZ(void *, void *);

void func_800CCC64(Wrestler *self, Wrestler *other, u32 flags) {
    f32 offset[3];
    f32 xOff;
    f32 zOff;
    s16 dir;
    s32 rot;
    f32 *otherPos;

    xOff = func_800D3564(self->x);
    zOff = func_800D3564(self->z);
    if (zOff <= xOff) {
        dir = 1;
        if (self->x < 0.0f) {
            dir = 3;
        }
    } else {
        dir = 0;
        if (self->z < 0.0f) {
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
        self->heading = func_800D35B0(self->heading, rot);
        other->heading = func_800D35B0(other->heading, rot);
        otherPos = &other->x;
        func_800D3B24(otherPos, &self->x, 0, offset);
        func_800D3E40(otherPos, offset, rot, offset);
        self->x = offset[0];
        self->z = offset[2];
    }
}
