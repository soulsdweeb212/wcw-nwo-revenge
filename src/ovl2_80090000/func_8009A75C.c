/* @header
 * func_8009A75C
 * VRAM 0x8009A75C | ROM 0x8DBFC | size 0x36C
 * asm: asm/nonmatchings/ovl2_80090000/func_8009A75C.s
 */
#include "common.h"

typedef struct {
    f32 x, y, z;
    u8 padC[8];
} Pos14;

void func_80097E34(s32, s16);
u16 func_800B8278(void);
s8 func_800A90FC(s16);
u16 func_800085E4(s16);
s8 func_800B83CC(s16);
void func_8009AAC8(void);
void func_8009B2EC(s16, u16 *);
void func_8009C774(s16, u16 *);
f32 func_80003CF0(f32);

extern u8 D_800706A0[];
extern f32 D_80070D10[][713];
extern f32 D_80070D18[][713];
extern s16 D_8007DFA8[];
extern u16 D_8007E280;
extern s16 D_800EB350;
extern f32 D_800EB3A0;
extern f32 D_800EB3A4;
extern s16 D_800F99BA;
extern Pos14 D_800F9AA8[];
extern s16 D_800FACEA[];

void func_8009A75C(s16 arg0) {
    u16 ids[4];
    u32 i;
    u16 r;
    u16 n;
    u16 v;
    s32 k;

    if ((D_800F99BA & 0x3F) == 0x21) {
        k = (D_800F99BA >> 8) - 1;
        func_80097E34(k, D_8007DFA8[k]);
    }
    for (i = 0; i < 4; i++) {
        ids[i] = i;
        if (D_800FACEA[i] >= 0) {
            Pos14 *p = &D_800F9AA8[i];

            p->x = -D_80070D10[i][0];
            p->y = D_80070D10[i][1];
            p->z = D_80070D18[i][0];
        }
    }
    r = func_800B8278();
    if (D_8007E280 & 0x200) {
        n = 4;
    } else {
        n = 0;
        for (i = 0; i < 4; i++) {
            if (D_800FACEA[i] >= 0 && ((r >> i) & 1)) {
                ids[n] = i;
                n++;
            }
        }
    }
    for (i = 0; i < n; i++) {
        if (((r >> ids[i]) & 1) && ((r >> func_800A90FC(ids[i])) & 1)) {
            v = func_800085E4(ids[i]);
            if (D_800F99BA == 0 && v != 0) {
                if (v < 8 || v >= 12) {
                    D_800F99BA = v + 0x13;
                    D_800F99BA = (v + 0x13) | ((ids[i] + 1) << 8);
                }
            }
            D_800706A0[ids[i]] = func_800B83CC(ids[i]);
        }
    }
    if (arg0 == 0) {
        if (n >= 3 && (D_800F99BA & 0x3F) < 0x20) {
            func_8009AAC8();
            D_800EB3A0 = 0.0f;
            D_800EB350 = 0;
        } else if ((D_800F99BA & 0x3F) < 0x14 || !(D_800F99BA & 0x700)) {
            func_8009B2EC(D_800F99BA, ids);
            D_800EB3A0 = 0.0f;
            D_800EB350 = 0;
        } else {
            if (D_800EB350 == 0) {
                D_800F99BA |= 0x40;
            }
            func_8009C774(D_800F99BA, ids);
            D_800F99BA = 0;
            D_800EB350 = 1;
        }
    }
    if (D_800EB3A0 != D_800EB3A4) {
        D_800EB3A4 += (D_800EB3A0 - D_800EB3A4) * 0.1;
        if (func_80003CF0(D_800EB3A4) < 0.1) {
            D_800EB3A4 = 0.0f;
        }
    }
}
