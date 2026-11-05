/* @header
 * func_8009791C
 * VRAM 0x8009791C | ROM 0x8ADBC | size 0xB0
 * asm: asm/nonmatchings/ovl2_80090000/func_8009791C.s
 */
#include "common.h"

extern u8 *D_800E2CF4[];
extern u8 *D_800E2D58[];
extern s16 D_800E7942;
extern s8 D_800F99B4;
extern u8 D_800F99B5;
extern s8 D_800F9A9E;
extern s16 D_800F9AA0;
extern s16 D_800F9AA2;
extern s8 D_800F9AF8;

void func_80097BB4(void);
void func_80096E34(s32);
s32 func_8000DEE4(s32);

/* Same body as func_8009786C. */
static inline void select(s32 n) {
    s32 v;

    if (D_800F9AA2 != 0) {
        D_800F99B4 = n;
        D_800F9A9E = 0;
        v = (s8)(D_800E2CF4[(s8)n][1] + 0x5C) / 2;
        D_800F9AF8 = v;
        D_800F99B5 = *D_800E2D58[(s8)n];
        if (v < 5) {
            D_800F9AA0 = 0x50;
        } else {
            D_800F9AA0 = 0x6F;
        }
        D_800E7942 = 0;
    } else {
        func_80097BB4();
    }
}

void func_8009791C(void) {
    select(8);
    func_80096E34(0);
    func_8000DEE4(0x4E);
}
