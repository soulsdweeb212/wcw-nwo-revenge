/* @header
 * func_8000F408
 * VRAM 0x8000F408 | ROM 0x10008 | size 0xF4
 * asm: asm/nonmatchings/main/func_8000F408.s
 */
#include "common.h"

extern s8 D_80036CAC[];
extern s32 D_80058A0C;
extern u8 D_80058A10[];
extern s32 D_80058F90;
extern u8 D_80058FA0[];
extern s32 D_80059520;
extern u8 D_80059528[];
extern s32 D_80059898;
extern u8 D_800598A0[];
extern s32 D_80059C10;
extern u8 D_80059C18[];
extern s32 D_80059CC8;
extern u8 D_80059CD0[];
extern s16 D_80059D82;
void freeResourceDescriptorArray(void *, s32, s8);

/* Free all six resource descriptor arrays -- the two arena-dependent ones with
 * the current arena's count, the others with their fixed counts 0x13/0x13/3/3 --
 * and zero their size counters. */
void func_8000F408(void) {
    freeResourceDescriptorArray(D_80058A10, D_80058A0C, D_80036CAC[D_80059D82]);
    freeResourceDescriptorArray(D_80058FA0, D_80058F90, D_80036CAC[D_80059D82]);
    freeResourceDescriptorArray(D_80059528, D_80059520, 0x13);
    freeResourceDescriptorArray(D_800598A0, D_80059898, 0x13);
    freeResourceDescriptorArray(D_80059C18, D_80059C10, 3);
    freeResourceDescriptorArray(D_80059CD0, D_80059CC8, 3);
    D_80058A0C = 0;
    D_80058F90 = 0;
    D_80059520 = 0;
    D_80059898 = 0;
    D_80059C10 = 0;
    D_80059CC8 = 0;
}
