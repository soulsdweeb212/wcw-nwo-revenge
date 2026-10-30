#include "common.h"

typedef struct {
    u8 f0;
    u8 x1[0x17];
    u8 f18;
    u8 x19[3];
    s8 f1C;
} Inner;

typedef struct {
    s8 f0;
    u8 x1[0x13];
    s16 h14;
    u8 x16[0xA];
    unsigned long long flags;
    u8 x28[0x32B];
    s8 f353;
    u8 x354[0x10];
    Inner *p364;
    u8 x368[0x2B];
    u8 b393;
    s8 b394;
} Ent;

extern s16 D_800E37F0[][2];
extern u16 D_800E37F2[][2];
extern s16 D_800E3808[][2];
extern u16 D_800E380A[][2];
extern s16 D_800E3820[][4];
extern float D_800E3824[][2];
extern s16 D_800E3848[][2];
extern u16 D_800E384A[][2];
extern s16 D_800E3860[][4];
extern float D_800E3864[][2];
extern float D_800E38B4[];
extern u16 D_800E38CC[];
extern double D_800E5648;
extern double D_800E5650;
extern u16 D_800F9D24[][472];
extern s16 D_800F9B68[];

s32 func_800BF2FC(void *);

s32 func_800B71F8(Ent *a, Ent *b, s16 kind) {
    s16 lvl;
    s16 val;
    s32 diff;
    s16 i;
    s32 h;

    lvl = func_800BF2FC(a);
    switch (kind) {
    case 0:
        if (a->h14 >= D_800E37F0[0][0]) {
            val = D_800E37F2[0][0];
        } else {
            i = 0;
        inc0:
            i++;
            if (a->h14 < D_800E37F0[i][0]) goto inc0;
            val = D_800E37F2[i][0];
        }
        break;
    case 1:
        h = a->h14;
        diff = (s16)((s8)((s8)a->p364->f18 / 3) - (s8)((s8)b->p364->f18 / 3));
        i = 0;
    loop1:
        if (h < D_800E3808[i][0]) {
            i++;
            goto loop1;
        }
        val = D_800E380A[i][0];
        if (diff > 0) {
            val = val * 2.0;
        }
        break;
    case 2:
        if (a->flags & 0x80000) {
            return 0;
        }
        if (D_800E3820[0][0] <= lvl) {
            val = D_800E3824[0][0];
        } else {
            i = 0;
        inc2:
            i++;
            if (lvl < D_800E3820[i][0]) goto inc2;
            val = D_800E3824[i][0];
        }
        break;
    case 3:
        if (a->h14 >= D_800E3848[0][0]) {
            val = D_800E384A[0][0];
        } else {
            i = 0;
        inc3:
            i++;
            if (a->h14 < D_800E3848[i][0]) goto inc3;
            val = D_800E384A[i][0];
        }
        break;
    case 4: {
        s16 m = D_800F9D24[b->f353][0];
        s8 n = a->b393;
        s8 w = b->p364->f0;
        val = (15 - w - n - m / 30) * D_800E5648;
        break;
    }
    case 5:
        val = D_800E38B4[a->b394];
        break;
    case 6: {
        s8 t1C = a->p364->f1C;
        s32 c = D_800F9B68[a->f0] - 1;
        val = (D_800E38CC[t1C] + c * 6) * D_800E5650;
        break;
    }
    case 7:
        if (D_800E3860[0][0] <= lvl) {
            val = D_800E3864[0][0];
        } else {
            i = 0;
        inc7:
            i++;
            if (lvl < D_800E3860[i][0]) goto inc7;
            val = D_800E3864[i][0];
        }
        break;
    case 8:
        val = 1;
        func_800BF2FC(a);
        break;
    case 9:
        val = (a->h14 + b->h14) * D_800E5648;
        break;
    case 10: case 11: case 12: case 13: case 14:
    case 15: case 16: case 17: case 18:
        break;
    }
    return val;
}
