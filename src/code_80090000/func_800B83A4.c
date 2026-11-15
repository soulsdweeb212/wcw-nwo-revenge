/* @header
 * func_800B83A4
 * VRAM 0x800B83A4 | ROM 0x64B14 | size 0x2C
 * asm: asm/nonmatchings/code_80090000/func_800B83A4.s
 */
#include "common.h"

extern f32 D_800DC8CC;
extern f32 D_800DC8D0;
#ifdef TARGET_PC
/* PC: D_800DC8D4 is element 5 of the six floats D_800DC8C0 (func_800B83D0 reads them as f32). */
extern f32 D_800DC8D4;
#else
extern s32 D_800DC8D4;
#endif
extern s32 D_800DC8E4;

#ifdef TARGET_PC
/* PC: the third argument is a float: the caller func_800BB6E8 passes three f32 and a flag. On the N64 the third travels
 * as its bits in a2, which this function stores as they are; on PC floats travel in registers of their own, so the PC
 * definition takes it as an f32. */
void func_800B83A4(f32 arg0, f32 arg1, f32 arg2, s32 arg3) {
#else
void func_800B83A4(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
#endif
    D_800DC8CC = arg0;
    D_800DC8D0 = arg1;
    D_800DC8D4 = arg2;
    if (arg3 != 0) {
        D_800DC8E4 = 0;
    }
}
