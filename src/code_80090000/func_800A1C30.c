/* @header
 * func_800A1C30
 * VRAM 0x800A1C30 | ROM 0x4E3A0 | size 0x528
 * asm: asm/nonmatchings/code_80090000/func_800A1C30.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u8 pad0[4]; V *addr; u16 n; u8 padA[6]; } VtxSet;
typedef struct { u8 pad0[0xE]; u8 idx; } Def;
typedef struct {
    u8 pad0[0x14];
    s16 f14;
    u8 pad16[0xA];
    u16 f20;
    u8 pad22[2];
    Def *def;
} Obj;

extern V *D_800E7CB4;
extern VtxSet D_800CB7B8[];
extern s32 D_800CCBF8[];
u32 func_8001CE80(V *);

#define SHL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define SPVERTEX(g, v, n, v0) { G *_g = (g); _g->w0 = SHL(1, 24, 8) | SHL((n), 12, 8) | SHL((v0) + (n), 1, 7); _g->w1 = func_8001CE80(v); }
#define VTX(s, dx, dy) {                    \
    V *v = D_800E7CB4++;                    \
    v->ob[0] = (s)->ob[0] + (dx);           \
    v->ob[1] = (s)->ob[1] + (dy);           \
    v->ob[2] = (s)->ob[2];                  \
    v->flag = 0;                            \
    v->tc[0] = (s)->tc[0];                  \
    v->tc[1] = (s)->tc[1];                  \
    v->cn[0] = (s)->cn[0];                  \
    v->cn[1] = (s)->cn[1];                  \
    v->cn[2] = (s)->cn[2];                  \
    v->cn[3] = (s)->cn[3];                  \
}

static inline void wobble(s32 *x, s32 *y, s32 n) {
    s32 i;
    x[0] = D_800CCBF8[n & 0xF];
    i = n - 1;
    x[1] = D_800CCBF8[i & 0xF];
    i = n - 2;
    x[2] = D_800CCBF8[i & 0xF];
    i = n - 3;
    x[3] = D_800CCBF8[i & 0xF];
    i = n - 4;
    y[0] = D_800CCBF8[i & 0xF];
    i = n - 5;
    y[1] = D_800CCBF8[i & 0xF];
    i = n - 6;
    y[2] = D_800CCBF8[i & 0xF];
    i = n - 7;
    y[3] = D_800CCBF8[i & 0xF];
}

void func_800A1C30(G **dl, Obj *t) {
    s32 x[4];
    s32 y[4];
    G *g = *dl;
    V *s = D_800CB7B8[t->def->idx].addr;

    wobble(x, y, t->f14);
    if ((t->f20 & 0xFF00) == 0x6200) {
        SPVERTEX(g++, D_800E7CB4, 8, 0);
    } else {
        SPVERTEX(g++, D_800E7CB4, 4, 0);
    }
    VTX(&s[0], -x[0], -y[0]);
    VTX(&s[1], x[1], -y[1]);
    VTX(&s[2], -x[2], y[2]);
    VTX(&s[3], x[3], y[3]);
    if ((t->f20 & 0xFF00) == 0x6200) {
        VTX(&s[4], -x[0], y[0]);
        VTX(&s[5], x[1], y[1]);
        VTX(&s[6], -x[2], -y[2]);
        VTX(&s[7], x[3], -y[3]);
    }
    *dl = g;
}
