/* @header
 * func_8009786C
 * VRAM 0x8009786C | ROM 0x8AD0C | size 0xB0
 * asm: asm/nonmatchings/ovl2_80090000/func_8009786C.s
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

void func_8009786C(s32 n) {
    s32 v;

    if (D_800F9AA2 != 0) {
        D_800F99B4 = n;
        D_800F9A9E = 0;
#ifdef TARGET_PC
        /* PC: the tables hold s16 values in the PC's byte order (func_80096FE8 reads them as s16), so the N64's byte 1
         * of entry 0, its low byte, is the low byte of the s16. */
        v = (s8)((u8)((s16 *)D_800E2CF4[(s8)n])[0] + 0x5C) / 2;
#else
        v = (s8)(D_800E2CF4[(s8)n][1] + 0x5C) / 2;
#endif
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
