/* @header
 * func_800B807C
 * VRAM 0x800B807C | ROM 0x647EC | size 0x1E8
 * asm: asm/nonmatchings/code_80090000/func_800B807C.s
 */
#include "common.h"

typedef struct { u8 *p; u32 n; } R;
typedef struct { R *r; u16 a; u16 b; } P;
extern P D_800D2530[];
extern s32 D_800DC8E0, D_800DC8E4, D_800DC900[], D_800DC918[];
extern u8 D_800DC950[][0x100];
s32 func_800B7F3C(s32);
void func_800B5AE0(R *, void *);

s32 func_800B807C(s32 a, s32 b) {
    s32 i, x, y, d;
    R *q;

    if (a >= 0 && a == b) {
        goto single;
    }
    for (i = 0; i < 6; i++) {
        if (D_800DC918[i]) {
            return -1;
        }
    }
    if (a < 0) {
        return 0;
    }
    x = -1;
    y = -1;
    for (i = 0; D_800D2530[i].r; i++) {
        if (D_800D2530[i].a == a && D_800D2530[i].b == b) {
            y = i;
        }
        if (D_800D2530[i].a == b && D_800D2530[i].b == a) {
            x = i;
        }
    }
    d = 1;
    if (y < 0) {
        if (x < 0) {
            return -1;
        }
        D_800DC8E0 = x;
        d = -1;
    } else {
        D_800DC8E0 = y;
    }
    q = D_800D2530[D_800DC8E0].r;
    if (q->n < 4) {
single:
        return func_800B7F3C(b);
    }
    for (i = 0; i < 6; i++, q++) {
        func_800B5AE0(q, D_800DC950[i]);
        if (d > 0) {
            D_800DC900[i] = 0;
        } else {
            D_800DC900[i] = *(s16 *)(q->p + q->n * 8 - 4);
        }
        D_800DC918[i] = d;
    }
    D_800DC8E4 = 0;
    return 0;
}
