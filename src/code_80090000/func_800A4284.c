/* @header
 * func_800A4284
 * VRAM 0x800A4284 | ROM 0x509F4 | size 0x468
 * asm: asm/nonmatchings/code_80090000/func_800A4284.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u8 pad[0xE]; s16 h; s16 w; } T;
typedef struct { u8 pad0[0x16]; u8 f16; u8 f17; u8 pad18[8]; u16 f20; } Item;
typedef struct { u8 on; u8 on2; u8 pad2[0x16]; } Slot;
typedef struct { u8 pad0[0x628]; Slot slot[4]; s32 ids[4]; } Cfg;

extern V *D_800E7CB4;
extern s32 D_8007E8C0[];
extern struct { u8 pad0[8]; u16 mode; } D_8007EF30;
extern Cfg D_8007E228;
extern u8 D_800E7C60[][8];
extern u8 D_800CCCA4[], D_800CCCAC[], D_800CCCB4[];
extern f64 D_800D6208;
u32 osVirtualToPhysical(V *);
void func_800B6FE0(G **, s32);
T *func_800B75D4(G **, void *, s32);
void *func_8002AD34(s32, s32);

#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }

void func_800A4284(G **dl, Item *it) {
    G *g = *dl;
    s32 f = it->f20 & 0xFF;
    s32 n = D_8007E8C0[it->f20 & 3] - 1;
    void *src;
    T *t;
    s32 hw;

    if (f & 8) {
        EMIT(0xDF000000, 0);
    } else {
        EMIT(0xFA000000, (it->f16 / 3) & 0xFF);
        if (D_8007EF30.mode & 0x80) {
            func_800B6FE0(&g, (f & 3) | 0xCC);
            EMIT(0x07000206, 0x604);
        } else if (!(f & 4)) {
            func_800B6FE0(&g, n + 0xCC);
            EMIT(0x07000206, 0x604);
        }
        if ((f & 0x10) && D_800E7C60[n][0]) {
            EMIT(0xFA000000, it->f16 >> 1);
        } else {
            EMIT(0xFA000000, it->f16);
        }
        if (D_8007EF30.mode & 0x80) {
            if (D_8007E228.slot[f & 3].on) {
                if (D_8007E228.slot[f & 3].on2) {
                    src = D_800CCCB4;
                } else {
                    src = D_800CCCA4;
                }
            } else {
                src = D_800CCCAC;
            }
            t = func_800B75D4(&g, src, 8);
        } else {
            t = func_800B75D4(&g, func_8002AD34(D_8007E228.ids[f & 3], D_8007E8C0[0x1C + (f & 3)]), 8);
        }
        if (t->w > 0x60) {
            hw = 0x18;
        } else {
            hw = t->w * 7 * D_800D6208;
        }
        { G *_g = g++; _g->w0 = 0x01004018; _g->w1 = osVirtualToPhysical(D_800E7CB4); }
        {
            V *v = D_800E7CB4++;
            v->ob[0] = -hw; v->ob[1] = -0x4E; v->ob[2] = 0; v->flag = 0;
            v->tc[0] = 0; v->tc[1] = 0;
            v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        }
        {
            V *v = D_800E7CB4++;
            v->ob[0] = hw; v->ob[1] = -0x4E; v->ob[2] = 0; v->flag = 0;
            v->tc[0] = t->w << 5; v->tc[1] = 0;
            v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        }
        {
            V *v = D_800E7CB4++;
            v->ob[0] = -hw; v->ob[1] = -0x42; v->ob[2] = 0; v->flag = 0;
            v->tc[0] = 0; v->tc[1] = t->h << 5;
            v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        }
        {
            V *v = D_800E7CB4++;
            v->ob[0] = hw; v->ob[1] = -0x42; v->ob[2] = 0; v->flag = 0;
            v->tc[0] = t->w << 5; v->tc[1] = t->h << 5;
            v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        }
        EMIT(0x07101216, 0x00101614);
        if (f & 0x10) {
            EMIT(0xE7000000, 0);
            EMIT(0xFA000000, (it->f17 << 24) | (it->f17 << 16) | (it->f17 << 8) | it->f16);
            func_800B75D4(&g, D_800E7C60[n], 0x88);
            EMIT(0x07080A0E, 0x00080E0C);
        }
    }
    *dl = g;
}
