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
