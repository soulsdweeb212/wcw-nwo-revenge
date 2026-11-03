/* @header
 * func_800BF65C
 * VRAM 0x800BF65C | ROM 0x6BDCC | size 0x35C
 * asm: asm/nonmatchings/code_80090000/func_800BF65C.s
 */
#include "common.h"

typedef struct { u16 f0; u16 f2; u16 f4; s16 len; s16 v[4]; u16 flags; u16 f12; } Key;
typedef struct { Key *keys; f32 x, y, z; s32 r; s16 idx; s16 t; u16 f18; u16 f1A; } Anim;
typedef struct {
    u8 pad0[0x680];
    f32 f680;
    f32 f684;
    f32 f688;
    s32 f68C;
    u8 pad690[2];
    s16 f692;
    s16 f694;
    u8 pad696[4];
    u16 f69A;
    u8 pad69C[0x14];
    s16 f6B0;
    u8 pad6B2[2];
    s16 f6B4;
    s16 f6B6;
    s16 f6B8;
    s16 f6BA;
    s16 f6BC;
    s16 f6BE;
    u8 pad6C0[4];
    s32 f6C4;
    u8 pad6C8[8];
} Wr;

extern Wr *D_800E79B8;
extern Anim D_800DF330[];
extern s32 D_800E9F70;
void func_80012B38(s16, s32, s32);
void func_80012364(s16, s16, s32, s32);
void func_800BF2F0(Wr *, Anim *);
void func_800C2DA0(s32, f32 *, s32);

void func_800BF65C(void) {
    Wr *w = D_800E79B8;
    Anim *a;
    Key *k;
    s32 i, n, x, y;
    u16 t;

    for (i = 0, a = D_800DF330; i < 4; i++, w++, a++) {
        if ((s32)a->keys >= 0) {
            continue;
        }
        if (a->idx < 0) {
            w->f6BE = 0;
            a->t = 1;
            w->f6B6 = -1;
            w->f6B0 = 0;
            n = 1;
        } else {
            w->f6BE = 2;
            k = &a->keys[a->idx];
            if (w->f6C4 & 0x80) {
                if (w->f6BA == 0 && w->f692 == w->f694) {
                    if (D_800E9F70 < 0) {
                        w->f6C4 = 4;
                    } else {
                        w->f6C4 = 0;
                    }
                    x = -1;
                    y = -1;
                    switch (w->f69A & 0xF0) {
                    case 0x30:
                        y = 2;
                        break;
                    case 0x10:
                        x = 4;
                        break;
                    case 0x40:
                        y = 0xA;
                        break;
                    }
                    func_80012B38(i, x, 2);
                    func_80012364(i, i, y, 0);
                } else {
                    w->f6B6 = 0;
                }
            }
            if (a->idx >= 0) {
                func_800BF2F0(w, a);
            }
            w->f680 = a->x;
            w->f684 = a->y;
            w->f688 = a->z;
            w->f68C = a->r;
            if (++a->f18 >= w->f6B8) {
                a->f18 = 0;
                w->f6B6 = 0;
            }
            w->f6B4 = a->f18;
            n = k->len;
        }
        if (n != 0) {
            if (n < 0) {
                n = w->f6B8 - k->f2;
            }
            if (a->t >= n) {
                a->idx++;
                a->t = 0;
                if (a->idx != 0 && !(k->flags & 0x8000)) {
                    func_800C2DA0(i, &a->x, 0);
                }
                k = &a->keys[a->idx];
                if (k->flags & 0x2000) {
                    w->f6BE = 2;
                }
                if (k->flags & 0x1000) {
                    w->f6BE = 0;
                }
                if (k->flags & 0x4000) {
                    a->x = k->v[0];
                    a->y = k->v[1];
                    a->z = k->v[2];
                    a->r = k->v[3];
                    if (a->idx >= 0) {
                        func_800BF2F0(w, a);
                    }
                    w->f680 = a->x;
                    w->f684 = a->y;
                    w->f688 = a->z;
                    w->f68C = a->r;
                }
                t = k->f4;
                w->f6BC = t;
                if (w->f6B0 != (s16)t) {
                    w->f6B0 = t;
                    w->f6B4 = a->f18 = k->f2;
                    w->f6B6 = 0;
                }
            }
        }
        a->t++;
    }
}
