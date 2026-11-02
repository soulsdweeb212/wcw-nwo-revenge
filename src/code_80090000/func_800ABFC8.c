/* @header
 * func_800ABFC8
 * VRAM 0x800ABFC8 | ROM 0x58738 | size 0x17C
 * asm: asm/nonmatchings/code_80090000/func_800ABFC8.s
 */
#include "common.h"

typedef struct { u8 pad0[0xA]; u16 a; s8 c; s8 d; s8 e; u8 pad1; s16 f; u8 pad2[0x136]; } P;
typedef struct { u8 pad0[4]; u16 k; u8 pad1[0xE]; P *p; } A;
s16 func_800A06F8(P *, s8);

void func_800ABFC8(A *a) {
    P *t = a->p;
    s32 n = -1;
    s32 m;
    P *q;
    s8 x;

    switch ((s16)a->k) {
    case 6:
        if (t[6].e == 1) {
            n = 0xC;
            m = 1;
        }
        break;
    case 0xC:
        if (t[0xC].e == 0) {
            n = 6;
            m = 0;
        }
        break;
    case 2:
        if (t[2].e != 3) {
            n = 0xE;
            m = 1;
        }
        break;
    case 0xA:
        if (t[0xA].e != 1) {
            n = 0xE;
            m = 1;
        }
        break;
    case 0xE:
        if (t[0xE].e == 0) {
            t[0xA].e = 1;
            t[0xA].d = 1;
            t[0xA].c = 1;
            t[0xA].f = func_800A06F8(&t[0xA], 1);
            n = 2;
            m = 3;
        }
        break;
    case 0x12:
        if (t[0x12].e == 1) {
            a->p[0x14].a |= 0x40;
            a->p[0x15].a |= 0x40;
        } else {
            a->p[0x14].a &= ~0x40;
            a->p[0x15].a &= ~0x40;
        }
        break;
    }
    if (n >= 0) {
        x = m;
        t[n].d = x;
        t[n].e = x;
        t[n].c = x;
        t[n].f = func_800A06F8(&t[n], x);
    }
}
