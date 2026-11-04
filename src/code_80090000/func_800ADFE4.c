/* @header
 * func_800ADFE4
 * VRAM 0x800ADFE4 | ROM 0x5A754 | size 0xDC
 * asm: asm/nonmatchings/code_80090000/func_800ADFE4.s
 */
#include "common.h"

typedef struct { u8 pad0[0xC]; s8 c; u8 d; u8 e; u8 padF; s16 h; u8 pad12[0x290 - 0x12]; } T;
extern T *D_800E8D3C;
extern u8 D_8007E8C0[], D_8007EF30[];
extern s32 D_800EA0B8;
extern s16 D_800E8D2C;
s16 func_800A06F8(T *, s32);

void func_800ADFE4(void) {
    T *p = D_800E8D3C;
    s32 i;
    p[0].e = D_8007E8C0[0x66D];
    p[2].e = D_8007E8C0[0x66E];
    p[1].e = D_8007E8C0[0x66F];
    p[3].e = D_8007EF30[0];
    p[4].e = D_8007EF30[3];
    p[5].e = D_8007EF30[1];
    p[6].e = D_8007EF30[2];
    for (i = 0, p = D_800E8D3C; i < 8; i++, p++) {
        u8 e = p->e;
        p->c = e;
        p->d = e;
        p->h = func_800A06F8(p, p->c);
    }
    D_800EA0B8 = 0;
    D_800E8D2C = 0x10;
}
