/* @header
 * func_800A9F30
 * VRAM 0x800A9F30 | ROM 0x566A0 | size 0x34
 * asm: asm/nonmatchings/code_80090000/func_800A9F30.s
 */
#include "common.h"

extern u8 D_8007EF30[];
#define F(t, o, i) (*(t *)(D_8007EF30 + (o) + ((i) << 4)))

void func_8002AD34(s32, s32);

void func_800A9F30(s32 i) {
    func_8002AD34(F(s16, 0x4E, i), F(u8, 0x50, i));
}
