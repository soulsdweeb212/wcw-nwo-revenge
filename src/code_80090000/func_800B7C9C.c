/* @header
 * func_800B7C9C
 * VRAM 0x800B7C9C | ROM 0x6440C | size 0x2A0
 * asm: asm/nonmatchings/code_80090000/func_800B7C9C.s
 */
#include "common.h"

typedef struct { f32 v; s16 t; s16 pad; } K;
typedef struct { K *k; u32 n; } C;
typedef struct { C *c; s32 x; } E;
extern E D_800D2530[];
extern f32 D_800DC8C0, D_800DC8C4, D_800DC8C8;
extern s32 D_800DC8D8, D_800DC8DC, D_800DC8E0, D_800DC8E4;
extern s32 D_800DC900[], D_800DC918[6];
extern f32 D_800DC930[6];
extern f64 D_800DC950[][32];
extern s32 D_800E8208;
f32 func_800B5D20(s32, C *, f64 *);
void func_800B8368(f32, f32, f32, f32, f32, f32);

static inline s32 step(s32 t, C *c, f64 *d, f32 *o0) {
    f32 *o = o0;
    u32 i = 0;
    K *k = c->k;
    u32 n = c->n;
    for (; i < n; i++, k++) {
        if (k->t >= t) {
            break;
        }
    }
    if (i == c->n) {
        *o = c->k[i - 1].v;
        return 0;
    }
    *o = func_800B5D20(t, c, d);
    return -1;
}

void func_800B7C9C(s32 a) {
    f64 (*d)[32] = D_800DC950;
    f32 *o = D_800DC930;
    s32 *b = D_800DC918;
    C *c = D_800D2530[D_800DC8E0].c;
    s32 *s = b;
    s32 *t = D_800DC900;
    do {
        if (*s != 0) {
            if (*s > 0) {
                *t += D_800E8208 * 5;
                if (step(*t, c, *d, o) == 0) {
                    *t = 0;
                    *s = 0;
                }
            } else {
                *t -= D_800E8208 * 5;
                if (*t < 0) {
                    *t = 0;
                    *s = 0;
                }
                step(*t, c, *d, o);
            }
        }
        d++;
        o++;
        s++;
        t++;
        c++;
#ifdef TARGET_PC
        /* PC: the two addresses compared as pointers; the N64 compares them as s32, which would cut them to 32 bits. */
    } while (s < b + 6);
#else
    } while ((s32)s < (s32)(b + 6));
#endif
    if (a == 0) {
        func_800B8368(D_800DC930[0], D_800DC930[1], D_800DC930[2], D_800DC930[3], D_800DC930[4], D_800DC930[5]);
        if (D_800DC8E4 == 0) {
            D_800DC8DC = 0;
            D_800DC8D8 = 0;
            D_800DC8E4 = -1;
            D_800DC8C0 = D_800DC930[0];
            D_800DC8C4 = D_800DC930[1];
            D_800DC8C8 = D_800DC930[2];
        }
    }
}
