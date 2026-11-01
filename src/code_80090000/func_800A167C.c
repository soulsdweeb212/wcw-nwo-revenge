/* @header
 * func_800A167C
 * VRAM 0x800A167C | ROM 0x4DDEC | size 0x64
 * asm: asm/nonmatchings/code_80090000/func_800A167C.s
 */
#include "common.h"

s32 allocateHeap(s32);                                /* extern */
s32 func_800A1590();                                  /* extern */
extern s32 D_800DC730;
extern s32 D_800DC734;
extern s32 D_800DC73C;
extern s32 D_800DC740;
extern f32 D_800DC828;

void func_800A167C(void) {
    D_800DC73C = 0;
    D_800DC828 = 1.0f;
    D_800DC734 = allocateHeap(0x10000);
    D_800DC740 = allocateHeap(0x4000);
    D_800DC730 = allocateHeap(0x14800);
    func_800A1590();
}
