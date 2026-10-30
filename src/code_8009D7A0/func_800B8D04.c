/* @header
 * func_800B8D04
 * VRAM 0x800B8D04 | ROM 0xAC1A4 | size 0x88
 * asm: asm/nonmatchings/code_8009D7A0/func_800B8D04.s
 */
#include "common.h"

extern void func_8009678C(void);
extern void func_80096018(void);
extern void func_800DA8B4(void *, s32, s32);
extern void func_800B9730(void *, void *, s32, s32);
extern s16 func_800BF2FC(void *);
extern s8 D_8007E8C0[];
extern u8 D_800E3978[], D_800EB468[], D_800FACE8;
extern s8 D_800EB46E, D_800EB46F;
extern u8 D_800FAF60[][6];
extern s16 D_800EB472;
extern u8 D_800F9D10[], D_800F9D1A[];
extern s8 D_800FA05C[], D_800FA063[], D_800FA0A6[];
/* Resets the four 6-byte D_800FAF60 records and the two player bytes. */
void func_800B8D04(void) {
    s16 i;
    D_800EB46E = 0;
    D_800EB46F = -1;
    func_80096018();
    for (i = 0; i < 4; i++) {
        func_800DA8B4(D_800FAF60[i], 0, 0);
    }
}
