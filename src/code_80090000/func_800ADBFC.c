/* @header
 * func_800ADBFC
 * VRAM 0x800ADBFC | ROM 0x5A36C | size 0x184
 * asm: asm/nonmatchings/code_80090000/func_800ADBFC.s
 */
#include "common.h"

extern u8 *D_800E85EC, *D_800E9AA4[];
extern u8 D_8007EF30[], D_800E85D8[];
extern s32 D_800D5F1C;

s32 func_800ADBFC(void) {
    u8 *p = D_800E85EC;
    u16 f = *(u16 *)(D_8007EF30 + 8);
    s32 r = 3;
    u8 *q = D_800E85D8;
    s32 n, i;
    s32 id;

    if (f & 0x8000) {
        if (f & 0x10) {
            id = 0x16;
            n = 0;
        } else if (D_800D5F1C < 2) {
            id = 0x2A;
            n = 0;
        } else {
            id = 0x29;
            n = 2;
        }
    } else {
        switch (f & 0xF0) {
        case 0x20:
            id = 0x1E;
            n = 6;
            break;
        case 0x40:
            id = 0x18;
            n = 6;
            break;
        case 0x80:
            id = 0x24;
            n = 5;
            break;
        default:
            id = 0x15;
            n = 3;
            break;
        }
    }
    if (n == 0) {
        *(s16 *)(p + 0x20) = id;
        *(s16 *)(q + 4) = 0;
        func_800ADD80(id);
        func_800B5300(0x40B);
        *(s16 *)(D_800E9AA4[0] + 0x3E0) = -1;
        r = 0xD;
        D_800E9AA4[0][0x3EE] = 0;
    } else {
        for (i = 0; i < n; i++, id++, p += 0x148) {
            *(u16 *)(p + 0xA) &= 0xFFBE;
            *(s16 *)(p + 0x20) = id;
        }
        for (; n < 6; n++) {
            *(u16 *)(p + 0xA) |= 1;
            p += 0x148;
        }
        *(s16 *)(q + 4) = 0;
        func_800AD970(q);
    }
    return r;
}
