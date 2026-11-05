/* @header
 * func_800B1D04
 * VRAM 0x800B1D04 | ROM 0x5E474 | size 0x184
 * asm: asm/nonmatchings/code_80090000/func_800B1D04.s
 */
#include "common.h"


typedef struct { u8 pad0[4]; s16 c; u8 pad1[0xE]; u8 *p; } Q;
extern Q D_800E9820;
extern u8 *D_800E9834;
extern u8 D_8007E8C0[];
extern s32 D_800E7BF0, D_800E7BF4, D_800E7BF8, D_800E7BFC;
extern s16 D_800E9824;

void func_800B1D04(s32 a) {
    u8 *p = D_800E9834;
    Q *q = &D_800E9820;
    s32 i, k;
    u8 *r;

    *(u16 *)(p + 0x3E2) &= 0xFFFE;
    *(u16 *)(p + 0x52A) &= 0xFFFE;
    if (a == 2) {
        *(s16 *)(p + 0x3F8) = 0x7D02;
        *(s16 *)(p + 0x540) = 0x7D00;
        bzero(D_8007E8C0 + 0x80, 0x19);
        bcopy(D_8007E8C0 + 0x80 + 0x38, D_8007E8C0 + 0x80, 0x19);
        D_800E7BF8 = 0;
    } else {
        *(s16 *)(p + 0x3F8) = 0x7D03;
        *(s16 *)(p + 0x540) = 0x7D01;
        bzero(D_8007E8C0 + 0x80, 0xB);
        bcopy(D_8007E8C0 + 0x80 + 0x5A, D_8007E8C0 + 0x80, 0xB);
        D_800E7BF8 = 1;
    }
    p = q->p;
    for (i = 0; i < 3; i++, p += 0x148) {
        *(u16 *)(p + 0xA) &= 0xFFFE;
    }
    D_800E7BF0 = 0;
    D_800E7BF4 = 0;
    D_800E7BFC = 0;
    *(s16 *)(q->p + 0x20) = 0x7C02;
    D_800E9824 = 0;
    for (k = 0; k < 0x57; k++) {
        i = k * 8;
        r = D_8007E8C0 + 0x80 + i;
        *(s32 *)(r + 0x80) = 0;
        *(s32 *)(D_8007E8C0 + 0xFC + i) = 0;
        *(s32 *)(r + 0x338) = 0;
        *(s32 *)(D_8007E8C0 + 0x3B4 + i) = 0;
    }
    D_800E7BF4 = 6;
    D_800E7BF0 = 0;
    D_800E9824 = 2;
}
