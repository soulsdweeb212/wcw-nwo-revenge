/* @header
 * func_800BB2A0
 * VRAM 0x800BB2A0 | ROM 0x67A10 | size 0xB8
 * asm: asm/nonmatchings/code_80090000/func_800BB2A0.s
 */
#include "common.h"

s32 allocateHeap(s32);                                /* extern */
s32 func_80000A40();                                /* extern */
s32 osCreateMesgQueue(s32 *, s32 *, s32);                       /* extern */
s32 func_800B8C4C(s32);                               /* extern */
s32 func_800B9268(s32);                                 /* extern */
s32 func_800BAD80();                                  /* extern */
extern s32 D_80038AAC;
extern s8 D_80038AB0;
extern s32 D_800D2970;
extern s32 D_800DCFB8;
extern s32 D_800DCFC0;
extern s32 D_800DCFD4;
extern u8 D_800DCFF0[];
extern u8 D_800DCFF8[];

void func_800BB2A0(void) {
    s32 temp_v0;
    s32 var_s0;

    D_800DCFC0 = 0;
    D_80038AB0 = 0;
    if (D_80038AAC == 0) {
        temp_v0 = allocateHeap(0x2E00);
        var_s0 = 0;
        D_80038AAC = temp_v0;
        D_800DCFB8 = temp_v0;
        do {
            func_800B8C4C(var_s0);
            var_s0 += 1;
        } while (var_s0 < 4);
        func_800B9268(-1);
    } else {
        D_800DCFB8 = D_80038AAC;
    }
    D_800D2970 = 0;
    D_800DCFD4 = func_80000A40();
    osCreateMesgQueue(&D_800DCFF8, &D_800DCFF0, 1);
    func_800BAD80();
}
