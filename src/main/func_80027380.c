/* @header
 * func_80027380
 * VRAM 0x80027380 | ROM 0x27F80 | size 0x10
 * asm: asm/nonmatchings/main/func_80027380.s
 */
#include "common.h"

s32 func_80027380(void) {
    return *(vu32 *)0xA4040010;
}

extern s32 D_8007BD60;
s32 nw2DisableInterrupts(void);
s32 func_80026AF0(void);
void nw2RestoreInterrupts(s32);
void func_80028100(s32, s32);
