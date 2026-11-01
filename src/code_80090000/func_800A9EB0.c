/* @header
 * func_800A9EB0
 * VRAM 0x800A9EB0 | ROM 0x56620 | size 0x4C
 * asm: asm/nonmatchings/code_80090000/func_800A9EB0.s
 */
#include "common.h"

extern u8 D_8007EF30[];
#define F(t, o, i) (*(t *)(D_8007EF30 + (o) + ((i) << 4)))

void func_800A9EB0(s32 i, s32 a, s32 b, s32 c, s32 e, s32 d) {
    F(s16, 0x4C, i) = a;
    F(s16, 0x4E, i) = b;
    F(u8, 0x50, i) = c;
    F(u8, 0x52, i) = e;
    F(u8, 0x51, i) = d;
}
