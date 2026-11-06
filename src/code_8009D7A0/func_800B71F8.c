/* @header
 * func_800B71F8
 * VRAM 0x800B71F8 | ROM 0xAA698 | size 0x838
 * asm: asm/nonmatchings/code_8009D7A0/func_800B71F8.s
 */
#include "common.h"

/* The character profile (Wrestler.profile) as this function reads it. */
typedef struct {
    u8 f0;
    u8 x1[0xF];
    s8 f10;
    u8 x11[0x7];
    u8 f18;
    u8 x19[3];
    s8 f1C;
} Profile71F8;

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
extern s16 D_800F9B68[];

s16 func_800BF2FC(void *);
s8 func_800D4198(s16);

s8 func_800B71F8(Wrestler *a, Wrestler *b, s16 kind) {
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
            if (a->spirit >= D_800E37F0[i].lim) {
                val = D_800E37F0[i].val;
                break;
            }
        }
        break;
    case 1:
        diff = (s8)((s8)((Profile71F8 *)a->profile)->f18 / 3) - (s8)((s8)((Profile71F8 *)b->profile)->f18 / 3);
        for (i = 0;; i++) {
            if (a->spirit >= D_800E3808[i].lim) {
                val = D_800E3808[i].val;
                if (diff > 0) {
                    val = val * 2.0;
                }
                break;
            }
        }
        break;
    case 2:
        if (a->flags & WR_FLAG_SPECIAL) {
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
            if (a->spirit >= D_800E3848[i].lim) {
                val = D_800E3848[i].val;
                break;
            }
        }
        break;
    case 4:
        n = 15 - (s8)a->move.stunBits - (s8)((Profile71F8 *)b->profile)->f0 - D_800F9D10[b->opponentId].spirit / 30;
        val = D_800E5648 / (f32)n * D_800E5670;
        break;
    case 5:
        val = D_800E38B4[(s8)a->move.koBits];
        break;
    case 6:
        n = D_800E38CC[((Profile71F8 *)a->profile)->f1C] + (D_800F9B68[a->id] - 1) * 6;
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
        if (a->flags & WR_FLAG_SPECIAL) {
            return 0;
        }
        for (i = 0;; i++) {
            if (lvl >= D_800E3880[i].lim) {
                val = (f32)((100 - a->spirit) / 40) / D_800E3880[i].val * D_800E5658;
                break;
            }
        }
        break;
    case 9:
        for (i = 0;; i++) {
            if (a->spirit >= D_800E3890[i].lim) {
                val = D_800E3890[i].val;
                break;
            }
        }
        break;
    case 10:
        val = D_800E5660 / (f32)(3 - ((Profile71F8 *)a->profile)->f10) * D_800E5670;
        break;
    case 11:
        if (a->flags & WR_FLAG_SPECIAL) {
            val = 1000;
            break;
        }
        diff = (s8)((s8)((Profile71F8 *)b->profile)->f18 / 3) - (s8)((s8)((Profile71F8 *)a->profile)->f18 / 3);
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
            if (a->spirit >= D_800E3938[i].lim) {
                val = D_800E3938[i].val;
                break;
            }
        }
        break;
    case 13:
        n = lvl / 10 + a->spirit / 10 + 1;
        val = D_800E5668 / (f32)n * D_800E5670;
        break;
    case 14:
        for (i = 0;; i++) {
            if (a->escapeTimer >= D_800E394C[i].lim) {
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
