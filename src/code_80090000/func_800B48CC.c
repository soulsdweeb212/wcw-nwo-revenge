/* @header
 * func_800B48CC
 * VRAM 0x800B48CC | ROM 0x6103C | size 0x158
 * asm: asm/nonmatchings/code_80090000/func_800B48CC.s
 */
#include "common.h"

typedef struct { u8 pad[0xA]; u16 f; u8 pad2[0x14]; u16 x; u16 y; u8 pad3[0x124]; } N;
extern N *D_800E96FC, *D_800E95C4;
extern s16 D_80038A90, D_800E95B4, D_800E96EC;
extern u8 D_800EA0D8[];
extern u16 D_800CD24C[];
s32 func_800BA940(void *, s32);

s32 func_800B48CC(s32 k) {
    N *p;
    s32 t, c, i;
    u16 v;
    if (D_80038A90 == 0x10) {
        p = D_800E96FC;
        t = 0;
        c = 0;
    } else {
        p = D_800E95C4;
        t = 1;
        c = 0x10;
    }
    if (k == 1 || k == 4) {
        c |= 0x80;
    } else if (k == 7) {
        c |= 0x80;
    }
    for (i = 0; i < 10; i++, p++) {
        p->x = (i + 0x7601) | c;
        p->y = 0;
        p->f &= 0xFFDF;
    }
    func_800BA940(D_800EA0D8 + t * 0xA0, (k << 4) | 0xF);
    p->x = D_800CD24C[k * 2];
    p->f &= 0xFFDF;
    p++;
    v = D_800CD24C[k * 2 + 1];
    p->f &= 0xFFDF;
    p->x = v;
    if (D_80038A90 == 0x10) {
        D_800E96EC = 10;
        return 0x11;
    }
    D_800E95B4 = 10;
    return 0x10;
}
