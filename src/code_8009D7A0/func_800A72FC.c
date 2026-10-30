/* @header
 * func_800A72FC
 * VRAM 0x800A72FC | ROM 0x9A79C | size 0x2C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A72FC.s
 */
#include "common.h"

void func_800D3838(s32, s32, s16, s32);

/* Forwards the entity's local position and the given parameters to
 * func_800D3838. */
void func_800A72FC(s32 arg0, s32 arg1, s32 arg2) {
    func_800D3838(arg0 + 0x6C, arg1, arg2, arg0 + 0x33C);
}

void func_800D36B4(void *, void *, void *);
void translateEntityXZ(void *, void *);

s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
