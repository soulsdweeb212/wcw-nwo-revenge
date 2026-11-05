/* @header
 * func_800A6498
 * VRAM 0x800A6498 | ROM 0x52C08 | size 0x68C
 * asm: asm/nonmatchings/code_80090000/func_800A6498.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u8 pad0[4]; u32 img; u8 pad8[4]; s16 width; s16 height; s16 h; } Spr;
typedef struct { u8 pad0[0x16]; u8 f16; u8 f17; u8 pad18[9]; u8 f21; } Item;

extern V *D_800E7CB4;
extern u8 D_8007E8C0[];
extern s32 D_800E7BF4, D_800E7BF8, D_800E7BFC;
extern u8 D_800E7542;
u32 osVirtualToPhysical(V *);
Spr *func_800B600C(u8 *, s32);
void func_800996B0(G **, s32, s32);
void func_800A2BC0(G **, Spr *, s32 *, s32 *, s32, s32);
void func_800B6FE0(G **, s32);

#define _SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#define TRI_W(v0, v1, v2) (_SHIFTL((v0) * 2, 16, 8) | _SHIFTL((v1) * 2, 8, 8) | _SHIFTL((v2) * 2, 0, 8))
#define QUAD(pkt, v0, v1, v2, v3) \
    { G *_g = (G *)(pkt); _g->w0 = (_SHIFTL(0x07, 24, 8) | TRI_W(v0, v1, v2)); _g->w1 = TRI_W(v0, v2, v3); }
#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }
#define VTX(X, Y, S, T, C) { V *v = D_800E7CB4++; v->ob[0] = (X); v->ob[1] = (Y); v->ob[2] = 0; v->flag = 0; \
    v->tc[0] = (S); v->tc[1] = (T); v->cn[0] = (C); v->cn[1] = (C); v->cn[2] = (C); v->cn[3] = 0xFF; }

void func_800A6498(G **dl, Item *it) {
    G *g = *dl;
    s32 n = it->f21;
    Spr *spr = NULL;
    s32 shown = 0;
    u8 *name;
    s32 id;
    s32 k, h;
    s32 x[4], y[4];
    u32 r, lo;
    s32 a, b;

    switch (n) {
    case 0:
    case 1:
        name = D_8007E8C0 + 0x80;
        id = 0x134;
        break;
    case 2:
        name = D_8007E8C0 + 0xB8;
        id = 0x133;
        break;
    case 3:
        id = 0x133;
        name = D_8007E8C0 + 0xDA;
        break;
    }
    y[0] = y[1] = -7;
    y[2] = y[3] = 7;
    x[0] = x[2] = 0;
    switch (n) {
    case 0:
    case 2:
        k = 8;
        h = 0xF0;
        x[1] = x[3] = 0xD2;
        break;
    case 1:
    case 3:
        k = 0xA;
        h = 0x78;
        x[1] = x[3] = 0x69;
        break;
    }
    EMIT(0xFA000000, ((it->f17 >> 1) << 24) | ((it->f17 >> 1) << 16) | ((it->f17 >> 1) << 8) | (it->f16 >> 1));
    EMIT(0xE7000000, 0);
    EMIT(0xFC51FEA3, 0x44FE773B);
    EMIT(0x07000206, 0x604);
    if (name != NULL) {
        spr = func_800B600C(name, 0x80000008);
        QUAD(g++, 4, k, k + 1, 5);
        if (h < spr->h) {
            h = spr->h;
        }
    }
    if (n == D_800E7BF8 && D_800E7BF4 < 6 && (D_800E7542 & 0xC0)) {
        /* An int, not the literal: the ROM loads the first vertex's colour into its own register. */
        s32 c = 0xFF;

        r = func_80029C40(name, 8, D_800E7BFC);
        lo = r & 0xFFFF;
        a = lo * x[1] / h;
        b = (lo + ((r >> 16) & 0xFF)) * x[1] / h + 1;
        { G *_g = g++; _g->w0 = 0x01004028; _g->w1 = osVirtualToPhysical(D_800E7CB4); }
        VTX(a, -6, 0, 0, c);
        VTX(b, -6, 0, 0, 0xFF);
        VTX(a, 8, 0, 0, 0xFF);
        VTX(b, 8, 0, 0, 0xFF);
        shown = 1;
        EMIT(0x07202226, 0x202624);
    }
    EMIT(0xE7000000, 0);
    EMIT(0xFC5196A3, 0x112CFE7F);
    EMIT(0xFA000000, (it->f17 << 24) | (it->f17 << 16) | (it->f17 << 8) | it->f16);
    func_800996B0(&g, id, 8);
    EMIT(0x07000206, 0x604);
    if (name != NULL) {
        func_800A2BC0(&g, spr, x, y, 4, h);
    }
    if (shown) {
        { G *_g = g++; _g->w0 = 0x01004028; _g->w1 = osVirtualToPhysical(D_800E7CB4); }
        VTX(a - 1, -7, 0, 0, 0xFF);
        VTX(b + 1, -7, 0x200, 0, 0xFF);
        VTX(a - 1, 9, 0, 0x200, 0xFF);
        VTX(b + 1, 9, 0x200, 0x200, 0xFF);
        func_800B6FE0(&g, 0xE6);
        EMIT(0x07202226, 0x202624);
    }
    *dl = g;
}
