/* @header
 * func_800A8140
 * VRAM 0x800A8140 | ROM 0x548B0 | size 0x2BC
 * asm: asm/nonmatchings/code_80090000/func_800A8140.s
 */
#include "common.h"

typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u32 w0, w1; } G;
typedef struct { u8 pad[0xE]; s16 h; s16 w; } T;
extern V *D_800E7CB4;
u32 func_8001CE80(V *);
s32 func_800A9F30(s32);
T *func_800B75D4(G **, s32, s32);

void func_800A8140(G **dl, s32 k, s32 a, s32 b) {
    G *g = *dl;
    G *p;
    G *q;
    G *r;
    V *v;
    T *t;
    s32 n, m, x0, y0, x1, y1;
    r = g++;
    r->w0 = 0xE7000000;
    r->w1 = 0;
    t = func_800B75D4(&g, func_800A9F30(k), 8);
    if (t != 0) {
        n = 0x40;
        if (t->w < 0x40) {
            n = t->w;
        }
        m = n / 2;
        p = g++;
        p->w0 = 0x01004010;
        x0 = (a - m) * 0x30 / 68;
        y0 = (b - 10) * 12 / 20;
        x1 = (a + m) * 0x30 / 68;
        y1 = (b + 10) * 12 / 20;
        p->w1 = func_8001CE80(D_800E7CB4);
        v = D_800E7CB4++;
        v->ob[0] = x0; v->ob[1] = y0; v->ob[2] = 0; v->flag = 0;
        v->tc[0] = 0; v->tc[1] = 0;
        v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        v = D_800E7CB4++;
        v->ob[0] = x1; v->ob[1] = y0; v->ob[2] = 0; v->flag = 0;
        v->tc[0] = t->w << 5; v->tc[1] = 0;
        v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        v = D_800E7CB4++;
        v->ob[0] = x0; v->ob[1] = y1; v->ob[2] = 0; v->flag = 0;
        v->tc[0] = 0; v->tc[1] = t->h << 5;
        v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        v = D_800E7CB4++;
        v->ob[0] = x1; v->ob[1] = y1; v->ob[2] = 0; v->flag = 0;
        v->tc[0] = t->w << 5; v->tc[1] = t->h << 5;
        v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        q = g++;
        q->w0 = 0x07080A0E;
        q->w1 = 0x80E0C;
        *dl = g;
    }
}
