/* @header
 * func_800BA59C
 * VRAM 0x800BA59C | ROM 0x66D0C | size 0x1C4
 * asm: asm/nonmatchings/code_80090000/func_800BA59C.s
 */
#include "common.h"


typedef struct {
    u16 p : 2, f13 : 1, f12 : 1, f11 : 1, f10 : 1, f7 : 3, f6 : 1, f5 : 1, f4 : 1, f3 : 1, f0 : 3;
    u16 q : 13, g : 3;
} B;
typedef struct { u8 pad[0x1A]; B b[2]; } T;
extern T *D_800DCFB8;
extern u8 D_8007EF30[];

#ifdef TARGET_PC
/* PC: the options are 16-bit values that func_800BA760 builds with shifts: bits 0-2 the first option, bit 3, 4, 5, 6
 * single options, bits 7-9 another, bits 10-13 single options again, and the next u16 with three bits of its own.
 * The N64 reads them through the bit-fields of B, laid out from the top bit down, and their low bytes at +0x1B, +0x1D
 * (+0x1F, +0x21), the second byte of each u16. A PC lays bit-fields out from the bottom bit up and keeps a u16's low
 * byte first, so the same bits are taken from the whole u16 with shifts. */
s32 func_800BA59C(s32 a) {
    u8 *t = (u8 *)D_800DCFB8 + (a == 0 ? 0x1A : 0x1E);
    u16 v = *(u16 *)t;

    D_8007EF30[0x1A2] = (v >> 3) & 1;
    D_8007EF30[0x1A3] = (v >> 4) & 1;
    D_8007EF30[0x1A4] = (v >> 5) & 1;
    D_8007EF30[0x1A5] = (v >> 6) & 1;
    D_8007EF30[0x1A1] = (v >> 7) & 7;
    D_8007EF30[0x1A6] = (v >> 10) & 1;
    D_8007EF30[0x1A7] = (v >> 11) & 1;
    D_8007EF30[0x1A8] = (v >> 12) & 1;
    D_8007EF30[0x1A9] = (v >> 13) & 1;
    D_8007EF30[0x1A0] = v & 7;
    D_8007EF30[0x1AA] = *(u16 *)(t + 2) & 7;
    return 0;
}
#else
s32 func_800BA59C(s32 a) {
    T *t;
    u8 x;

    if (a == 0) {
        t = D_800DCFB8;
        x = ((u8 *)t)[0x1B];
        D_8007EF30[0x1A2] = t->b[0].f3;
        D_8007EF30[0x1A3] = t->b[0].f4;
        D_8007EF30[0x1A4] = t->b[0].f5;
        D_8007EF30[0x1A5] = t->b[0].f6;
        D_8007EF30[0x1A1] = t->b[0].f7;
        D_8007EF30[0x1A6] = t->b[0].f10;
        D_8007EF30[0x1A7] = t->b[0].f11;
        D_8007EF30[0x1A8] = t->b[0].f12;
        D_8007EF30[0x1A9] = t->b[0].f13;
        x &= 7;
        D_8007EF30[0x1A0] = x;
        D_8007EF30[0x1AA] = ((u8 *)t)[0x1D] & 7;
    } else {
        t = D_800DCFB8;
        x = ((u8 *)t)[0x1F];
        D_8007EF30[0x1A2] = t->b[1].f3;
        D_8007EF30[0x1A3] = t->b[1].f4;
        D_8007EF30[0x1A4] = t->b[1].f5;
        D_8007EF30[0x1A5] = t->b[1].f6;
        D_8007EF30[0x1A1] = t->b[1].f7;
        D_8007EF30[0x1A6] = t->b[1].f10;
        D_8007EF30[0x1A7] = t->b[1].f11;
        D_8007EF30[0x1A8] = t->b[1].f12;
        D_8007EF30[0x1A9] = t->b[1].f13;
        x &= 7;
        D_8007EF30[0x1A0] = x;
        D_8007EF30[0x1AA] = ((u8 *)t)[0x21] & 7;
    }
    return 0;
}
#endif
