/* @header
 * func_800A83FC
 * VRAM 0x800A83FC | ROM 0x54B6C | size 0x7B4
 * asm: asm/nonmatchings/code_80090000/func_800A83FC.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { s32 x0, y0, x1, y1; } Box;
typedef struct { u8 pad0[8]; s16 f8; u8 padA[0x16]; u16 f20; u16 f22; } Obj;

extern V *D_800E7CB4;
extern s32 D_800CCF8C[];
extern s32 D_800CCBF8[];
extern u16 D_800C9254[];
extern struct { u8 pad0[0xA]; u16 fA; } D_8007EF30;
u32 osVirtualToPhysical(V *);
void func_800B6FE0(G **, s32);
void func_800B7260(G **, s32, s32, s32);
s32 func_800A9F64(s32);
void func_800A8140(G **, s32, s32, s32);

#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }
#define SPVERTEX(n, v0) { G *_g = g++; _g->w0 = 0x01000000 | ((n) << 12) | (((v0) + (n)) << 1); _g->w1 = osVirtualToPhysical(D_800E7CB4); }
#define VTX(x, y, s, t) {                   \
    V *v = D_800E7CB4++;                    \
    v->ob[0] = (x);                         \
    v->ob[1] = (y);                         \
    v->ob[2] = 0;                           \
    v->flag = 0;                            \
    v->tc[0] = (s);                         \
    v->tc[1] = (t);                         \
    v->cn[0] = 0xFF;                        \
    v->cn[1] = 0xFF;                        \
    v->cn[2] = 0xFF;                        \
    v->cn[3] = 0xFF;                        \
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

void func_800A83FC(G **dl, Obj *o) {
    s32 x[4];
    s32 y[4];
    G *g = *dl;
    s32 sel = o->f20 & 0xF;
    Box *b = (Box *)&D_800CCF8C[o->f22];
    s32 i;
    s32 x0, y0, x1, y1;

    EMIT(0xFC5196A3, 0x112CFE7F);
    if (o->f8 == 0 && sel != 0xF) {
        x0 = b[sel].x0 * 48 / 64;
        y0 = b[sel].y0 * 12 / 16;
        x1 = b[sel].x1 * 48 / 64;
        y1 = b[sel].y1 * 12 / 16;
        EMIT(0xE7000000, 0);
        SPVERTEX(4, 0);
        VTX(x0, y0, 0, 0);
        VTX(x1, y0, 0xFE0, 0);
        VTX(x0, y1, 0, 0x3E0);
        VTX(x1, y1, 0xFE0, 0x3E0);
        func_800B6FE0(&g, D_800C9254[0]);
        EMIT(0x07000206, 0x604);
    }
    x0 = -12;
    y0 = -6;
    x1 = 12;
    y1 = 6;
    EMIT(0xE7000000, 0);
    SPVERTEX(4, 4);
    VTX(x0, y0, 0, 0);
    VTX(x1, y0, 0x3E0, 0);
    VTX(x0, y1, 0, 0x200);
    VTX(x1, y1, 0x3E0, 0x200);
    func_800B7260(&g, 0x50, 0x10, 0x58);
    EMIT(0x07080A0E, 0x80E0C);
    for (i = 0; i < 4; i++) {
        if (b[i].x0 != 0) {
            if (i == sel) {
                wobble(x, y, D_8007EF30.fA & 0x1FF);
            } else {
                y[3] = 0;
                y[2] = 0;
                y[1] = 0;
                y[0] = 0;
                x[3] = 0;
                x[2] = 0;
                x[1] = 0;
                x[0] = 0;
            }
            x0 = b[i].x0 * 48 / 64;
            y0 = b[i].y0 * 12 / 16;
            x1 = b[i].x1 * 48 / 64;
            y1 = b[i].y1 * 12 / 16;
            EMIT(0xE7000000, 0);
            SPVERTEX(4, 4);
            VTX(x0 - x[0], y0 - y[0], 0x80, 0);
            VTX(x1 + x[1], y0 - y[1], 0x360, 0);
            VTX(x0 - x[2], y1 + y[2], 0x80, 0x200);
            VTX(x1 + x[3], y1 + y[3], 0x360, 0x200);
            func_800B7260(&g, func_800A9F64(i) * 16, 0x10, 0x58);
            EMIT(0x07080A0E, 0x80E0C);
            func_800A8140(&g, i, b[i].x0 + 0xC, b[i].y0 + 8);
        }
    }
    EMIT(0xDF000000, 0);
    *dl = g;
}
