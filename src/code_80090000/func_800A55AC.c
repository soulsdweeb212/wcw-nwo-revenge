/* @header
 * func_800A55AC
 * VRAM 0x800A55AC | ROM 0x51D1C | size 0x484
 * asm: asm/nonmatchings/code_80090000/func_800A55AC.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u8 pad[0xE]; s16 h; s16 w; } T;
typedef struct { u8 pad0[0x16]; u8 f16; u8 f17; u8 pad18[0xA]; u16 f22; } Item;
typedef struct { s32 f0; u16 f4; u8 f6[4]; u16 fA; u8 fC[4]; } Ent;

extern V *D_800E7CB4;
extern struct { u8 pad0[0xA]; u16 fA; } D_8007EF30;
extern Ent D_800EA0D8[2][10];
extern f64 D_800D6230;
u32 func_8001CE80(V *);
T *func_800B75D4(G **, void *, s32);
T *func_800B7A00(G **, s32, s32);
void *func_8002AD34(s32, s32);
void *lookupPlayerNameById(void *, void *);
void func_800B7260(G **, s32, s32, s32);

#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }
#define VTX(X, Y, S, T) { V *v = D_800E7CB4++; v->ob[0] = (X); v->ob[1] = (Y); v->ob[2] = 0; v->flag = 0; v->tc[0] = (S); v->tc[1] = (T); v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF; }

static inline void drawId(G **pg, s32 id, s32 f) {
    G *g2 = *pg;
    T *u = func_800B7A00(&g2, id, f | 0x80000018);
    if (u->w >= 0x60) {
        { G *_g = g2++; _g->w0 = 0x02140008; _g->w1 = (u->w + 7) << 21; }
        { G *_g = g2++; _g->w0 = 0x0214000C; _g->w1 = ((u->w + 7) << 21) | 0x1C0; }
    }
    { G *_g = g2++; _g->w0 = 0x07080A0E; _g->w1 = 0x00080E0C; }
    *pg = g2;
}

void func_800A55AC(G **dl, Item *it, u32 k) {
    G *g = *dl;
    s32 f = 0;
    Ent *e;
    T *t;
    s16 hw;
    void *name;

    if (D_8007EF30.fA & 8) {
        f = it->f22;
    }
    EMIT(0xFA000000, (it->f17 << 24) | (it->f17 << 16) | (it->f17 << 8) | it->f16);
    e = &D_800EA0D8[(k >> 4) & 1][k & 0xF];
    if (e->fA) {
        t = func_800B75D4(&g, lookupPlayerNameById(func_8002AD34(e->f4 & 0xFFF, (e->f4 >> 12) & 3),
                                                   func_8002AD34(e->fA & 0xFFF, (e->fA >> 12) & 3)), f | 8);
    } else {
        t = func_800B75D4(&g, func_8002AD34(e->f4 & 0xFFF, (e->f4 >> 12) & 3), f | 8);
    }
    if (t->w >= 0x80) {
        EMIT(0x02140002, t->w << 21);
        EMIT(0x02140006, (t->w << 21) | 0x1C0);
    }
    EMIT(0x07000206, 0x604);
    drawId(&g, e->f0, f);
    if (e->fC[0]) {
        name = lookupPlayerNameById(e->f6, e->fC);
    } else {
        name = e->f6;
    }
    t = func_800B75D4(&g, name, f | 8);
    if (t->w <= 0x50) {
        hw = t->w * 7 * D_800D6230;
    } else {
        hw = 0x1A;
    }
    { G *_g = g++; _g->w0 = 0x01004018; _g->w1 = func_8001CE80(D_800E7CB4); }
    VTX(-hw, -6, 0, 0);
    VTX(hw, -6, t->w << 5, 0);
    VTX(-hw, 6, 0, t->h << 5);
    VTX(hw, 6, t->w << 5, t->h << 5);
    EMIT(0x07101216, 0x00101614);
    func_800B7260(&g, (k & 0xF) << 4, 0x10, 0xA4);
    EMIT(0x07181A1E, 0x00181E1C);
    *dl = g;
}
