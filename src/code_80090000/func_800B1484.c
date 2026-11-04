/* @header
 * func_800B1484
 * VRAM 0x800B1484 | ROM 0x5DBF4 | size 0x264
 * asm: asm/nonmatchings/code_80090000/func_800B1484.s
 */
#include "common.h"

typedef struct {
    u8 p0[0xA];
    u16 flags; /* 0A */
    u8 p1;
    u8 g;      /* 0D */
    u8 p2[2];
    s16 h;     /* 10 */
    u8 p3[2];
    s16 d;     /* 14 */
    u8 a;      /* 16 */
    u8 p4;
    u8 b;      /* 18 */
    u8 p5[7];
    u16 c;     /* 20 */
    u16 id;    /* 22 */
    u8 p6[0x148 - 0x24];
} El;
typedef struct { void *items; s16 cur; u8 pad6[8]; s16 e; u8 p10[2]; s16 s; El *el; u8 pad18[0x138 - 0x18]; } Menu;
typedef struct {
    u8 pad0[0xE];
    s16 fE;
    u16 f10;
    s16 f12;
    u8 pad14[0x18];
    u16 *f2C;
} Game;
extern Game D_8007EF30;
extern Menu D_800E8230[];
extern s32 D_800E7B58;
void func_800B1298(s32);
s32 func_800AAB64(Menu *, s32);

void func_800B1484(s32 n, s32 m) {
    Menu *mn = &D_800E8230[n];
    El *el, *p;
    s32 i, c;

    if (m < 0) {
        p = mn->el;
        for (i = 0; i < 11; i++, p++) {
            p->a = 0;
            p->d = 0xFF;
            p->b = 0;
        }
        mn->e = 0x88;
        mn->s = 0x10;
        mn->cur = 1;
    } else {
        if (m > 0) {
            if (n == 13) {
                mn->cur = D_800E8230[14].cur;
            } else {
                mn->cur = D_800E8230[13].cur;
            }
            mn->s = 0;
            mn->e = 0;
            func_800B1298(n);
            for (i = 0, p = mn->el; i < 11; i++, p++) {
                if (!(p->flags & 1)) {
                    if (p->flags & 0x40) {
                        p->a = 0x80;
                    } else {
                        p->a = 0xFF;
                    }
                }
                p->d = 0xFF;
                p->b = 0;
            }
        } else {
            D_8007EF30.f12 = 0;
            if (D_8007EF30.fE >= D_8007EF30.f2C[2]) {
                D_8007EF30.fE = D_8007EF30.f2C[2] - 1;
            }
            mn->cur = (u16)D_8007EF30.fE + 1;
            func_800B1298(n);
        }
        if (mn->el[mn->cur].flags & 0x2053) {
            mn->cur = func_800AAB64(mn, 0x800);
        }
    }
    mn->el[0].c = D_8007EF30.f10 + 0x5300;
    p = &mn->el[mn->cur];
    c = p->c;
    if ((c & 0xFF00) == 0x5000) {
        D_8007EF30.f12 = c & 3;
    }
    el = mn->el;
    el[10].id = el[mn->cur].id;
    el[10].g = 1;
    el[10].h = 0x80;
    el[10].flags = (el[10].flags | 1) & ~0x20;
    if (m > 0) {
        if (n == 13) {
            D_800E7B58 = -0x30;
        } else {
            D_800E7B58 = 0x30;
        }
    }
}
