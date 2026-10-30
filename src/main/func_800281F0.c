/* @header
 * func_800281F0
 * VRAM 0x800281F0 | ROM 0x28DF0 | size 0x18
 * asm: asm/nonmatchings/main/func_800281F0.s
 */
#include "common.h"

extern s32 D_800389A0;
extern u8 D_80064AC0[];
extern u8 D_80073E98[];
extern u8 D_80070A98;

extern s32 D_80037248;
extern void *D_80037250;

s32 func_8001C890(void *, void *, s32);
s32 func_8001C990(void *, void *, s32);
s32 func_8001CAC0(void *, s32, s32);
s32 nw2DisableInterrupts(void);
void func_800265AC(s32 *, s32);
void nw2RestoreInterrupts(s32);

s32 func_800281F0(void) {
    return (*(volatile u32 *)0xA4800018 & 3) != 0;
}
