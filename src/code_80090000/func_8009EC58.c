/* @header
 * func_8009EC58
 * VRAM 0x8009EC58 | ROM 0x4B3C8 | size 0x6A0
 * asm: asm/nonmatchings/code_80090000/func_8009EC58.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 f6;
    u16 f8;
    union {
        u16 flags;
        struct { u8 hi; u8 type; } b;
    } u;
} Spr;
typedef struct { u8 pad0[0x24]; f32 f24; } Obj;
typedef struct {
    u8 pad0[0x10];
    G *f10;
    Obj *f14;
    u8 f18;
    u8 pad19[3];
    u8 f1C[0xC0];
    Spr *fDC;
    s16 fE0;
    s16 fE2;
    u16 fE4;
    s16 fE6;
    u16 fE8;
    u16 fEA;
} P;

extern s32 D_800E797C;
extern s32 D_800E81F8;
extern u8 D_C9538[], D_C95F0[], D_C9620[], D_800C5C50[];
void func_800B830C(void *);
s32 func_800B6F88(s32, u8 **, u8 **);
u8 *func_800B64EC(s32, s32);
void func_8009C218(G **, P *, s32);
void func_80096D8C(G **, u8 *, s32, s32, s32, s32, s32, s32, s32);
void func_8009773C(G **, u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void buildTiledTextureDisplayList(G **, u8 *, s32, s32, s32, s32, s32, s32, s32, s32);

#define W(a, b) { G *_d = g++; _d->w0 = (u32)(a); _d->w1 = (u32)(b); }

void func_8009EC58(G **dl, P *p) {
    G *g;
    u8 *tex;
    u8 *pal;
    s32 skip;
    s32 alpha;
    s32 x;
    s32 y;
    s32 fmt;
    u8 *r;

    g = *dl;
    p->f10 = g;
    func_800B830C(p->f1C);
    skip = 0;
    if ((p->fE8 & 3) == 0) {
        p->f18 |= 0x80;
        W(0xDF000000, 0);
        return;
    }
    alpha = 0xFF;
    if (p->fDC->u.b.type == 0x14 && (D_800E797C >> 8) == 2) {
        {
            s32 t = p->fE0;
            if (p->fEA & 1) {
                x = t + 4;
            } else {
                x = t - 4;
            }
        }
        y = p->fDC->f6 * p->fE4 / 256 + p->fE2;
    } else if (p->fDC->u.flags & 0x200) {
        y = p->fDC->f6;
        alpha = p->fE6;
        x = (0x1E0 - p->fDC->f8) / 2;
    } else if (p->fDC->u.flags & 0x400) {
        x = p->fDC->f6 * p->fE4 / 256 + p->fE0;
        y = p->fE2;
    } else if (p->fDC->u.flags & 0x100) {
        x = p->fDC->f6 + p->fE0;
        y = p->fE2;
        alpha = p->fE6;
    } else {
        x = p->fE0;
        y = p->fDC->f6 * p->fE4 / 256 + p->fE2;
    }
    if (p->fDC->u.flags & 0x4000) {
        if (!(p->fDC->u.flags & 0x8000) && D_800E81F8 == 0) {
            skip = 1;
        }
    } else if (p->fDC->u.flags & 0x8000) {
        if (alpha == 0) {
            skip = 1;
        } else if (func_800B6F88(p->fDC->f0, &tex, &pal) == 0) {
            skip = 1;
        } else if (p->fDC->u.flags & 0x800) {
            tex = pal + 0x20;
        } else {
            tex = pal + 0x200;
        }
    } else if (D_800E81F8 != 0) {
        r = func_800B64EC(D_800E81F8, p->fDC->f0);
        pal = r + 0x10;
        if (p->fDC->u.flags & 0x800) {
            tex = r + 0x30;
        } else {
            tex = r + 0x210;
        }
    } else {
        skip = 1;
    }
    if (skip == 0) {
        if (p->fE8 & 1) {
            p->f18 = 0;
            p->f14->f24 = 8192.0f;
        } else {
            p->f18 = 5;
            p->f14->f24 = -8192.0f;
        }
        W(0xDE000000, D_C9538);
        W(0xE2001E01, 0);
        W(0xE200001C, 0x5041C8);
        W(0xE3001201, 0x2000);
        if (p->fDC->u.b.type != 0) {
            func_8009C218(&g, p, 1);
        }
        W(0xFB000000, 0);
        W(0xFA000000, alpha & 0xFF);
        if (!(p->fDC->u.flags & 0x4000)) {
            if (p->fDC->u.flags & 0x800) {
                W(0xFD100000, (u32)pal - 0x80000000);
                W(0xE8000000, 0);
                W(0xF5000100, 0x07000000);
                W(0xE6000000, 0);
                W(0xF0000000, 0x0703C000);
                W(0xE7000000, 0);
                fmt = 0;
            } else {
                W(0xFD100000, (u32)pal - 0x80000000);
                W(0xE8000000, 0);
                W(0xF5000100, 0x07000000);
                W(0xE6000000, 0);
                W(0xF0000000, 0x073FC000);
                W(0xE7000000, 0);
                fmt = 1;
            }
            if (p->fDC->u.flags & 0x2000) {
                W(0xDE000000, D_C9620);
                func_80096D8C(&g, tex, fmt, x, y, p->fDC->f2, p->fDC->f4, p->fDC->f2, p->fDC->f4);
            } else if (p->fDC->u.flags & 0x1000) {
                W(0xDE000000, D_C95F0);
                y = p->fDC->f6 + p->fE2;
                func_8009773C(&g, tex, fmt, p->fEA, x, y, p->fDC->f2, p->fDC->f4, p->fDC->f8, p->fDC->f4,
                              p->fDC->f2, 0, 10, 16);
                p->fEA++;
            } else {
                W(0xDE000000, D_C95F0);
                buildTiledTextureDisplayList(&g, tex, fmt, x, y, p->fDC->f2, p->fDC->f4,
                                             p->fDC->f8 * p->fE4 / 256, p->fDC->f4 * p->fE4 / 256, p->fDC->f2);
            }
        }
        if (p->fDC->u.b.type != 0) {
            func_8009C218(&g, p, 0);
        }
        W(0xDE000000, D_800C5C50);
    }
    W(0xDF000000, 0);
    *dl = g;
}
