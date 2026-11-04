/* @header
 * func_800C2370
 * VRAM 0x800C2370 | ROM 0x6EAE0 | size 0x394
 * asm: asm/nonmatchings/code_80090000/func_800C2370.s
 */
#include "common.h"

typedef struct { s16 x, z; u16 t; u16 pad; } Pt;
typedef struct { f32 x, y, z, w, t; u8 pad[0xC]; } Pos;
typedef struct { u8 pad0[0x680]; f32 f680, f684, f688; s32 f68C; u8 pad690[0x6D0 - 0x690]; } Wr;

extern Wr *D_800E79B8;
extern s32 D_800E74D8;
extern s32 D_800E7CC0[];
extern s32 D_800E74B8[];
extern Pt *D_800D5DA0[];
extern Pt *D_800D5990[];
s32 func_800966B8(void);
s32 func_800B5E18(s32, s32);

static inline Pt *get(s32 k, s32 idx) {
    if (D_800E74D8 == -9) {
        return &D_800D5DA0[k][idx];
    }
    return &D_800D5990[func_800966B8() * 4 + k][idx];
}

void func_800C2370(s32 i, s32 b) {
    Wr *w = &D_800E79B8[i];
    Pos pp[2];
    Pos *o;
    Pos *q;
    Pt *p;
    s32 n;
    s32 r, k;

    for (n = 0;; n++) {
        k = D_800E7CC0[i];
        o = &pp[0];
        p = get(k, n);
        o->x = p->x;
        o->z = p->z;
        o->t = p->t & 0xFC0;
        if ((p->t & 0xF) * 4 >= (b & 0xFC)) {
            break;
        }
    }
    n++;
    k = D_800E7CC0[i & 3];
    q = &pp[0];
    p = get(k, n);
    q->x = p->x;
    q->z = p->z;
    q->t = p->t & 0xFC0;
    k = D_800E7CC0[i & 3];
    p = get(k, n + 1);
    pp[1].x = p->x;
    pp[1].z = p->z;
    pp[1].t = p->t & 0xFC0;
    D_800E74B8[i] = n + 1;
    w->f680 = (s32)pp[0].x;
    w->f688 = (s32)pp[0].z;
    if (-300.0f < w->f680 && w->f680 < 300.0f && -300.0f < w->f688 && w->f688 < 300.0f) {
        w->f684 = 90.0f;
    }
    r = func_800B5E18(pp[1].x - pp[0].x, pp[1].z - pp[0].z);
    if (r >= 0) {
        w->f68C = r;
    }
}
