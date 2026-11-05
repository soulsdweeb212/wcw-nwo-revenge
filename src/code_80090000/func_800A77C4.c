/* @header
 * func_800A77C4
 * VRAM 0x800A77C4 | ROM 0x53F34 | size 0x470
 * asm: asm/nonmatchings/code_80090000/func_800A77C4.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
extern V *D_800E7CB4;
extern u16 D_800C91FC[], D_800C91CC[], D_800C9252[];
u32 osVirtualToPhysical(V *);
void func_800B6FE0(G **, s32);

#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }
#define VTX(X, Y, S, T, C) { V *v = D_800E7CB4++; v->ob[0] = (X); v->ob[1] = (Y); v->ob[2] = 0; v->flag = 0; v->tc[0] = (S); v->tc[1] = (T); v->cn[0] = (C); v->cn[1] = (C); v->cn[2] = (C); v->cn[3] = 0xFF; }

void func_800A77C4(G **dl, s32 x, s32 y, s32 w, s32 h, s32 f, s32 mode) {
    G *g = *dl;

    EMIT(0x01004008, osVirtualToPhysical(D_800E7CB4));
    switch (mode) {
    case 0x1001:
        VTX(-0x34, -0x1C, 0, 0, 0xFF);
        VTX(x - 0x2C, -0x1C, 0x800, 0, 0xC0);
        VTX(-0x34, y - 0x14, 0, 0x800, 0x80);
        VTX(x - 0x2C, y - 0x14, 0x800, 0x800, 0x40);
        func_800B6FE0(&g, D_800C91FC[0]);
        break;
    case 0x1002:
        VTX(-0x34, -0x1C, 0, 0, 0xFF);
        VTX(x - 0x2C, -0x1C, 0x800, 0, 0xC0);
        VTX(-0x34, y - 0x14, 0, 0x800, 0x80);
        VTX(x - 0x2C, y - 0x14, 0x800, 0x800, 0x40);
        func_800B6FE0(&g, D_800C91CC[0]);
        break;
    default:
        VTX(-0x34, -0x1C, f << 5, f << 5, 0xFF);
        VTX(x - 0x2C, -0x1C, (f + w) << 5, f << 5, 0xC0);
        VTX(-0x34, y - 0x14, f << 5, (f + h) << 5, 0x80);
        VTX(x - 0x2C, y - 0x14, (f + w) << 5, (f + h) << 5, 0x40);
        func_800B6FE0(&g, D_800C9252[0]);
        EMIT(0xF5400800, 0x14050);
        break;
    }
    EMIT(0x07000206, 0x604);
    *dl = g;
}
