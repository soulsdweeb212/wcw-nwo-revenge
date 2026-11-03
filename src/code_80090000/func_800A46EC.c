/* @header
 * func_800A46EC
 * VRAM 0x800A46EC | ROM 0x50E5C | size 0x56C
 * asm: asm/nonmatchings/code_80090000/func_800A46EC.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u8 pad[0xE]; s16 h; s16 w; } T;
typedef struct { s16 x; s16 y; u8 pad4[0x1C]; } Row;

extern V *D_800E7CB4;
extern u8 D_800D6210[], D_800D6214[];
u32 func_8001CE80(V *);
T *func_800B75D4(G **, void *, s32);
T *func_800B7A00(G **, s32, s32);
void *func_800995EC(s32);

#define SHL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define MODVTX(g, vtx, where, val) { G *_g = (g); _g->w0 = SHL(2, 24, 8) | SHL(where, 16, 8) | SHL((vtx) * 2, 0, 16); _g->w1 = (u32)(val); }
#define TRI_W1(v0, v1, v2) (SHL((v0) * 2, 16, 8) | SHL((v1) * 2, 8, 8) | SHL((v2) * 2, 0, 8))
#define SP2TRI(g, a0, a1, a2, b0, b1, b2) { G *_g = (g); _g->w0 = (SHL(7, 24, 8) | TRI_W1(a0, a1, a2)); _g->w1 = TRI_W1(b0, b1, b2); }
#define VTX(X, Y, S, T) { V *v = D_800E7CB4++; v->ob[0] = (X); v->ob[1] = (Y); v->ob[2] = 0; v->flag = 0; v->tc[0] = (S); v->tc[1] = (T); v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF; }

void func_800A46EC(G **dl, u32 k, s32 n, Row *r) {
    G *g = *dl;
    T *u;
    s32 w;

    if ((s32)k > 0 && (k & 0x1000000)) {
        { G *_g = g++; _g->w0 = 0x01004040; _g->w1 = func_8001CE80(D_800E7CB4); }
        VTX(-3, r[n + 1].y, 0, 0);
        VTX(-3, r[n + 2].y, 0x1C0, 0);
        VTX(3, r[n + 1].y, 0, 0x1C0);
        VTX(3, r[n + 2].y, 0x1C0, 0x1C0);
        func_800B75D4(&g, D_800D6210, 0x80000008);
        { G *_g = g++; _g->w0 = 0x07383C3E; _g->w1 = 0x00383E3A; }
        if (n == 9) {
            u = func_800B75D4(&g, func_800995EC(k & 0x3FFFF), 0x80000018);
        } else {
            u = func_800B7A00(&g, k & 0x3F, 0x80000018);
        }
        w = u->w;
        if (w < 0x23) {
            w = 0x23;
        }
        MODVTX(g++, n * 2 + 2, 0x14, w << 21);
        MODVTX(g++, 28, 0x14, 0);
        MODVTX(g++, n * 2 + 4, 0x14, (w << 21) | 0x1C0);
        MODVTX(g++, 29, 0x14, 0x1C0);
        SP2TRI(g++, n * 2 + 2, 28, 29, n * 2 + 2, 29, n * 2 + 4);
        if (n == 9) {
            u = func_800B75D4(&g, func_800995EC((k >> 6) & 0x3FFFF), 0x80000018);
        } else {
            u = func_800B7A00(&g, (k >> 6) & 0x3F, 0x80000018);
        }
        w = u->w;
        if (w < 0x23) {
            w = 0x23;
        }
        MODVTX(g++, 30, 0x14, w << 21);
        MODVTX(g++, n * 2 + 3, 0x14, 0);
        MODVTX(g++, 31, 0x14, (w << 21) | 0x1C0);
        MODVTX(g++, n * 2 + 5, 0x14, 0x1C0);
        SP2TRI(g++, 30, n * 2 + 3, n * 2 + 5, 30, n * 2 + 5, 31);
    } else {
        if ((s32)k < 0) {
            u = func_800B75D4(&g, D_800D6214, 0x80000018);
            w = u->w;
        } else {
            if (n == 9) {
                u = func_800B75D4(&g, func_800995EC(k), 0x80000018);
            } else {
                u = func_800B7A00(&g, k, 0x80000018);
            }
            w = u->w;
            if (w < 0x50) {
                w = 0x50;
            }
        }
        MODVTX(g++, n * 2 + 2, 0x14, w << 21);
        MODVTX(g++, n * 2 + 3, 0x14, 0);
        MODVTX(g++, n * 2 + 4, 0x14, (w << 21) | 0x1C0);
        MODVTX(g++, n * 2 + 5, 0x14, 0x1C0);
        SP2TRI(g++, n * 2 + 2, n * 2 + 3, n * 2 + 5, n * 2 + 2, n * 2 + 5, n * 2 + 4);
    }
    *dl = g;
}
