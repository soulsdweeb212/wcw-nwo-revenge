/* @header
 * func_800BB0CC
 * VRAM 0x800BB0CC | ROM 0x6783C | size 0x44
 * asm: asm/nonmatchings/code_80090000/func_800BB0CC.s
 */
#include "common.h"

s32 func_80000A40();                                /* extern */
s32 osCreateMesgQueue(s32 *, s32 *, s32);                       /* extern */
s32 func_800BAD80();                                  /* extern */
extern s32 D_800DCFD4;
extern u8 D_800DCFF0[];
extern u8 D_800DCFF8[];

void func_800BB0CC(void) {
    D_800DCFD4 = func_80000A40();
    osCreateMesgQueue(&D_800DCFF8, &D_800DCFF0, 1);
    func_800BAD80();
}
