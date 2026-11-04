/* @header
 * func_800B2F94
 * VRAM 0x800B2F94 | ROM 0x5F704 | size 0x564
 * asm: asm/nonmatchings/code_80090000/func_800B2F94.s
 */
#include "common.h"

typedef struct { s32 k; s32 v; } St;
typedef struct { St s[0x57]; } Pl;
typedef struct {
    u8 pad0[8];
    union { u32 w; u16 mode; } f8;
    u8 padC[0x1B0 - 0xC];
    Pl pl[4];
} Game;
/* D_8007EF30 + 0x170: a separate symbol, so the score table is not addressed off the mode register */
typedef struct { u16 f0; u8 pad2[6]; s32 best[10]; } Rec;
typedef struct { s32 w[10]; s32 sum; } Sc;
typedef struct { s16 a; s16 b; } Wt;

extern Game D_8007EF30;
extern Rec D_8007F0A0;
extern Sc D_800EA220[4];
extern u16 D_800CD820[];
extern Wt D_800CD0F0[];
extern s32 D_80038AA8;
void func_800B2D20(s32);
s32 func_800B2B18(s32);
s32 func_8000DEE4(s32);

/* One step of the results tally: arg0 is (stage << 8) | step, and the return value is the next one. */
s32 func_800B2F94(s32 arg0) {
    s32 snd = 0;
    s32 st = arg0 >> 8;
    s32 n = arg0 & 0xFF;
    s32 i, j, k;

    if (st >= 10) {
        return arg0;
    }
    if (D_8007EF30.f8.mode & 0x800) {
        if (st == 9) {
            for (st = 0; st < 10; st++) {
                D_800EA220[0].w[st] = D_8007F0A0.best[st];
                D_800EA220[1].w[st] = D_8007F0A0.best[st];
            }
        } else {
            D_800EA220[0].w[st] = (u32)(D_8007F0A0.best[st] * n) / 10;
            D_800EA220[1].w[st] = (u32)(D_8007F0A0.best[st] * n) / 10;
            n++;
            if (n < 10) {
                n = 0;
                st++;
            }
        }
    } else if (D_8007EF30.f8.mode & 0x80) {
        if (st == 9) {
            for (k = 0; k < 10; k++) {
                func_800B2D20(k);
            }
            st = 10;
        } else {
            func_800B2D20(st);
            st++;
        }
    } else if (st == 9) {
        for (i = 0; i < 4; i++) {
            j = 0;
            for (st = 0; st < 6; st++) {
                D_800EA220[i].w[st] = 0;
                for (; j < D_800CD820[st + 1]; j++) {
                    D_800EA220[i].w[st] += D_8007EF30.pl[i].s[j].v * D_800CD0F0[j].a;
                    D_800EA220[i].w[st] -= (D_8007EF30.pl[i].s[j].k - D_8007EF30.pl[i].s[j].v) * D_800CD0F0[j].b;
                }
            }
        }
        for (; st < 10; st++) {
            func_800B2B18(st);
        }
    } else if (st < 6) {
        j = D_800CD820[st] + n;
        for (i = 0; i < 4; i++) {
            D_800EA220[i].w[st] += D_8007EF30.pl[i].s[j].v * D_800CD0F0[j].a;
            D_800EA220[i].w[st] -= (D_8007EF30.pl[i].s[j].k - D_8007EF30.pl[i].s[j].v) * D_800CD0F0[j].b;
        }
        if (n == 0) {
            snd = 1;
        }
        n++;
        if (++j == D_800CD820[st + 1]) {
            n = 0;
            st++;
        }
    } else {
        snd = func_800B2B18(st);
        st++;
    }
    if (!(D_8007EF30.f8.mode & 0x80)) {
        if (D_8007EF30.f8.mode & 0x40) {
            D_800EA220[1].w[6] /= 2;
            D_800EA220[0].w[6] /= 2;
        }
        for (i = 0; i < 4; i++) {
            D_800EA220[i].sum = 0;
            for (j = 0; j < 10; j++) {
                D_800EA220[i].sum += D_800EA220[i].w[j];
            }
        }
        if (!(D_8007EF30.f8.mode & 0x800)) {
            if (D_8007EF30.f8.mode & 0x40) {
                D_800EA220[1].sum += D_800EA220[0].sum;
                D_800EA220[0].sum = D_800EA220[1].sum;
            } else if (D_8007EF30.f8.mode & 0x20) {
                D_800EA220[1].sum += D_800EA220[0].sum;
                D_800EA220[0].sum = D_800EA220[1].sum;
                D_800EA220[3].sum += D_800EA220[2].sum;
                D_800EA220[2].sum = D_800EA220[3].sum;
            }
        }
        if ((D_8007EF30.f8.w & 0x88000000) == 0x80000000) {
            D_8007F0A0.best[D_80038AA8] = D_800EA220[0].sum;
        }
    }
    for (i = 0; i < 4; i++) {
        if (D_800EA220[i].sum > 3999999) {
            D_800EA220[i].sum = 4000000;
        }
    }
    if (snd) {
        func_8000DEE4(0x406);
    }
    return (st << 8) | n;
}
