/* @header
 * func_800A289C
 * VRAM 0x800A289C | ROM 0x4F00C | size 0x258
 * asm: asm/nonmatchings/code_80090000/func_800A289C.s
 */
#include "common.h"

typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u32 w0, w1; } G;
typedef struct { u8 pad[0xE]; s16 h; s16 w; } T;
extern V *D_800E7CB4;
u32 osVirtualToPhysical(V *);

void func_800A289C(G **dl, T *t, s32 a, s32 b) {
    G *g = *dl;
    G *p;
    G *q;
    V *v;
    s32 x0, x1;
    s16 s, u; s32 w, c;
    if (b < 0) {
        w = t->w;
        x0 = 0;
        x1 = w * a / 64;
        s = w;
        u = 0;
    } else if (b > 0) {
        w = t->w;
        x0 = -w * a / 64;
        x1 = 0;
        s = w;
        u = 0;
    } else {
        c = t->w;
        s = 0;
        u = c;
        x1 = c * a / 127;
        x0 = -x1;
    }
    p = g++;
    p->w0 = 0x01004008;
    p->w1 = osVirtualToPhysical(D_800E7CB4);
    v = D_800E7CB4++;
    v->ob[0] = x0; v->ob[1] = -6; v->ob[2] = 0; v->flag = 0;
    v->tc[0] = s << 5; v->tc[1] = 0;
    v->cn[0] = 0; v->cn[1] = 0; v->cn[2] = 0; v->cn[3] = 0xFF;
    v = D_800E7CB4++;
    v->ob[0] = x1; v->ob[1] = -6; v->ob[2] = 0; v->flag = 0;
    v->tc[0] = u << 5; v->tc[1] = 0;
    v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
    v = D_800E7CB4++;
    v->ob[0] = x0; v->ob[1] = 6; v->ob[2] = 0; v->flag = 0;
    v->tc[0] = s << 5; v->tc[1] = t->h << 5;
    v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
    v = D_800E7CB4++;
    v->ob[0] = x1; v->ob[1] = 6; v->ob[2] = 0; v->flag = 0;
    v->tc[0] = u << 5; v->tc[1] = t->h << 5;
    v->cn[0] = 0; v->cn[1] = 0; v->cn[2] = 0; v->cn[3] = 0xFF;
    q = g++;
    q->w0 = 0x07000206;
    q->w1 = 0x604;
    *dl = g;
}
