/* @header
 * func_800A2158
 * VRAM 0x800A2158 | ROM 0x4E8C8 | size 0x744
 * asm: asm/nonmatchings/code_80090000/func_800A2158.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u8 pad0[0xC]; s8 fC; s8 fD; u8 padE[6]; s16 f14; } Obj;

extern V *D_800E7CB4;
extern const s32 D_800CCBF8[];
u32 func_8001CE80(V *);
void func_800B7260(G **, s32, s32, s32);

#define SHL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define SPVERTEX(g, v, n, v0) { G *_g = (g); _g->w0 = SHL(1, 24, 8) | SHL((n), 12, 8) | SHL((v0) + (n), 1, 7); _g->w1 = func_8001CE80(v); }
#define MODVTX(g, vtx, where, val) { G *_g = (g); _g->w0 = SHL(2, 24, 8) | SHL(where, 16, 8) | SHL((vtx) * 2, 0, 16); _g->w1 = (u32)(val); }
#define TRI_W1(v0, v1, v2) (SHL((v0) * 2, 16, 8) | SHL((v1) * 2, 8, 8) | SHL((v2) * 2, 0, 8))
#define SP2TRI(g, a0, a1, a2, b0, b1, b2) { G *_g = (g); _g->w0 = (SHL(7, 24, 8) | TRI_W1(a0, a1, a2)); _g->w1 = TRI_W1(b0, b1, b2); }
#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }
#define VTX(X, Y, S, T) { V *v = D_800E7CB4++; v->ob[0] = (X); v->ob[1] = (Y); v->ob[2] = 0; v->flag = 0; v->tc[0] = (S); v->tc[1] = (T); v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF; }

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

void func_800A2158(G **dl, Obj *o) {
    s32 x[6];
    s32 y[6];
    G *g = *dl;
    s32 a, b, ta, tb;

    EMIT(0xE7000000, 0);
    EMIT(0xD9FFF9FF, 0);
    EMIT(0xD9FFFFFF, 0x200);
    EMIT(0xE3001001, 0x8000);
    EMIT(0xFC5196A3, 0x112CFE7F);
    wobble(x, y, o->f14);
    x[0] = -0x2F - x[0];
    x[1] += 0x2F;
    x[2] = -0x2F - x[2];
    x[3] += 0x2F;
    y[0] = -35.0 - y[0];
    y[1] = -35.0 - y[1];
    y[2] = y[2] + 35.0;
    y[3] = y[3] + 35.0;
    x[4] = (x[0] + x[1]) / 2;
    x[5] = (x[2] + x[3]) / 2;
    y[4] = (y[0] + y[1]) / 2;
    y[5] = (y[2] + y[3]) / 2;
    SPVERTEX(g++, D_800E7CB4, 6, 0);
    VTX(x[0], y[0], 0, 0);
    VTX(x[4], y[4], 0x3E0, 0);
    VTX(x[1], y[1], 0x3E0, 0);
    VTX(x[2], y[2], 0, 0x5E0);
    VTX(x[5], y[5], 0x3E0, 0x5E0);
    VTX(x[3], y[3], 0x3E0, 0x5E0);
    if (o->fD & 1) {
        b = o->fD * 4;
        a = o->fC * 4;
    } else {
        a = o->fD * 4;
        b = o->fC * 4;
    }
    ta = a / 10;
    EMIT(0xE7000000, 0);
    func_800B7260(&g, ta * 48, 0x30, 0xEB);
    tb = b / 10;
    SP2TRI(g++, 0, 1, 4, 0, 4, 3);
    EMIT(0xE7000000, 0);
    MODVTX(g++, 0, 0x14, 0x5E0);
    MODVTX(g++, 1, 0x14, 0x03E005E0);
    MODVTX(g++, 3, 0x14, 0);
    MODVTX(g++, 4, 0x14, 0x03E00000);
    func_800B7260(&g, tb * 48, 0x30, 0xEB);
    SP2TRI(g++, 3, 4, 1, 3, 1, 0);
    EMIT(0xE7000000, 0);
    MODVTX(g++, 1, 0x14, 0);
    MODVTX(g++, 4, 0x14, 0x5E0);
    func_800B7260(&g, (a - ta * 10) * 48, 0x30, 0xEB);
    SP2TRI(g++, 1, 2, 5, 1, 5, 4);
    EMIT(0xE7000000, 0);
    MODVTX(g++, 1, 0x14, 0x5E0);
    MODVTX(g++, 2, 0x14, 0x03E005E0);
    MODVTX(g++, 4, 0x14, 0);
    MODVTX(g++, 5, 0x14, 0x03E00000);
    func_800B7260(&g, (b - tb * 10) * 48, 0x30, 0xEB);
    SP2TRI(g++, 4, 5, 2, 4, 2, 1);
    *dl = g;
}
