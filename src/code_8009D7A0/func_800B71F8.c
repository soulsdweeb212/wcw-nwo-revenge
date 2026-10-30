/* @header
 * func_800B71F8
 * VRAM 0x800B71F8 | ROM 0xAA698 | size 0x838
 * asm: asm/nonmatchings/code_8009D7A0/func_800B71F8.s
 */
#include "common.h"

typedef struct {
    u8 f0;
    u8 x1[0xF];
    s8 f10;
    u8 x11[0x7];
    u8 f18;
    u8 x19[3];
    s8 f1C;
} Inner;

typedef struct {
    s8 f0;
    u8 x1[0x13];
    s16 h14;
    u8 x16[2];
    s16 h18;
    u8 x1A[6];
    u64 flags;
    u8 x28[0x32B];
    s8 f353;
    u8 x354[0x10];
    Inner *p364;
    u8 x368[0x2B];
    u8 b393;
    s8 b394;
} Ent;

typedef struct { s16 lim; u16 val; } StepI;
typedef struct { s16 lim; f32 val; } StepF;

extern StepI D_800E37F0[];
extern StepI D_800E3808[];
extern StepF D_800E3820[];
extern StepI D_800E3848[];
extern StepF D_800E3860[];
extern StepF D_800E3880[];
extern StepF D_800E3890[];
extern f32 D_800E38B4[];
extern u16 D_800E38CC[];
extern StepI D_800E38D4[][5];
extern StepI D_800E3938[];
extern StepI D_800E394C[];
extern f64 D_800E5648, D_800E5650, D_800E5658, D_800E5660, D_800E5668, D_800E5670;
extern u16 D_800F9D24[][472];
extern s16 D_800F9B68[];

s16 func_800BF2FC(void *);
s8 func_800D4198(s16);

s8 func_800B71F8(Ent *a, Ent *b, s16 kind) {
    s16 lvl;
    s16 val;
    s16 i;
    s16 j;
    s16 diff;
    s16 n;

    lvl = func_800BF2FC(a);
    switch (kind) {
    case 0:
        for (i = 0;; i++) {
            if (a->h14 >= D_800E37F0[i].lim) {
                val = D_800E37F0[i].val;
                break;
            }
        }
        break;
    case 1:
        diff = (s8)((s8)a->p364->f18 / 3) - (s8)((s8)b->p364->f18 / 3);
        for (i = 0;; i++) {
            if (a->h14 >= D_800E3808[i].lim) {
                val = D_800E3808[i].val;
                if (diff > 0) {
                    val = val * 2.0;
                }
                break;
            }
        }
        break;
    case 2:
        if (a->flags & 0x80000) {
            return 0;
        }
        for (i = 0;; i++) {
            if (lvl >= D_800E3820[i].lim) {
                val = D_800E3820[i].val;
                break;
            }
        }
        break;
    case 3:
        for (i = 0;; i++) {
            if (a->h14 >= D_800E3848[i].lim) {
                val = D_800E3848[i].val;
                break;
            }
        }
        break;
    case 4:
        n = 15 - (s8)a->b393 - (s8)b->p364->f0 - (s16)D_800F9D24[b->f353][0] / 30;
        val = D_800E5648 / (f32)n * D_800E5670;
        break;
    case 5:
        val = D_800E38B4[a->b394];
        break;
    case 6:
        n = D_800E38CC[a->p364->f1C] + (D_800F9B68[a->f0] - 1) * 6;
        val = D_800E5650 / (f32)n * D_800E5670;
        break;
    case 7:
        for (i = 0;; i++) {
            if (lvl >= D_800E3860[i].lim) {
                val = D_800E3860[i].val;
                break;
            }
        }
        break;
    case 8:
        if (a->flags & 0x80000) {
            return 0;
        }
        for (i = 0;; i++) {
            if (lvl >= D_800E3880[i].lim) {
                val = (f32)((100 - a->h14) / 40) / D_800E3880[i].val * D_800E5658;
                break;
            }
        }
        break;
    case 9:
        for (i = 0;; i++) {
            if (a->h14 >= D_800E3890[i].lim) {
                val = D_800E3890[i].val;
                break;
            }
        }
        break;
    case 10:
        val = D_800E5660 / (f32)(3 - a->p364->f10) * D_800E5670;
        break;
    case 11:
        if (a->flags & 0x80000) {
            val = 1000;
            break;
        }
        diff = (s8)((s8)b->p364->f18 / 3) - (s8)((s8)a->p364->f18 / 3);
        if (diff >= 0) {
            j = diff + 1;
        } else {
            j = 0;
        }
        lvl = func_800BF2FC(b);
        for (i = 0;; i++) {
            if (lvl >= D_800E38D4[j][i].lim) {
                val = D_800E38D4[j][i].val;
                break;
            }
        }
        break;
    case 12:
        for (i = 0;; i++) {
            if (a->h14 >= D_800E3938[i].lim) {
                val = D_800E3938[i].val;
                break;
            }
        }
        break;
    case 13:
        n = lvl / 10 + a->h14 / 10 + 1;
        val = D_800E5668 / (f32)n * D_800E5670;
        break;
    case 14:
        for (i = 0;; i++) {
            if (a->h18 >= D_800E394C[i].lim) {
                val = D_800E394C[i].val;
                break;
            }
        }
        break;
    case 15:
        val = 700;
        break;
    case 16:
        val = 500;
        break;
    case 17:
        val = 600;
        break;
    case 18:
        val = 200;
        break;
    }
    if (val > 1000) {
        val = 1000;
    }
    return func_800D4198(val);
}
