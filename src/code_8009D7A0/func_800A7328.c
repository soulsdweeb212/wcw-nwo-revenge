/* @header
 * func_800A7328
 * VRAM 0x800A7328 | ROM 0x9A7C8 | size 0x3C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7328.s
 */
#include "common.h"

void func_800D3838(s32, s32, s16, s32);

void func_800D36B4(void *, void *, void *);
void translateEntityXZ(void *, void *);

/* Transform the entity's local offset (+0x4C) by its position and apply it. */
void func_800A7328(u8 *arg0) {
    u8 sp10[0x10];

    func_800D36B4(arg0 + 0x4C, arg0 + 0x6C, sp10);
    translateEntityXZ(arg0, sp10);
}

s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
