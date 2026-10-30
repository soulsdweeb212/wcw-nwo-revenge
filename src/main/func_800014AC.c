/* @header
 * func_800014AC
 * VRAM 0x800014AC | ROM 0x20AC | size 0x24
 * asm: asm/nonmatchings/main/func_800014AC.s
 */
#include "common.h"

extern u8 D_80048288[8];
extern s32 D_80046860[];
extern s16 D_80047062;
extern u8 *D_80046858;
extern s16 D_80047060;

void multiplyMatrix4x4(s32, s32, void *);
void func_8001C0F0(void *, s32, s32, f32);
void initIdentityMatrix4x4(void *);

/* Multiply matrix arg2 by arg1 into the D_80048288 scratch result; arg0 is
 * unused by this wrapper. */
void func_800014AC(s32 arg0, s32 arg1, s32 arg2) {
    multiplyMatrix4x4(arg2, arg1, D_80048288);
}
