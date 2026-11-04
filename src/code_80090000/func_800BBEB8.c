/* @header
 * func_800BBEB8
 * VRAM 0x800BBEB8 | ROM 0x68628 | size 0x474
 * asm: asm/nonmatchings/code_80090000/func_800BBEB8.s
 */
#include "common.h"

extern struct { u8 pad0[4]; u8 f4; u8 pad5[3]; u16 mode; } D_8007EF30;
extern struct { u8 pad0[0x688]; s32 ids[8]; } D_8007E228;
extern s32 D_8007E8B8;
extern s32 D_8007E8C0[];
extern s32 D_800EA0AC, D_800EA0A8, D_800E74BC, D_800E74B8, D_800EA320, D_800DF1E0, D_800DF1E8, D_800DF1E4;
extern s32 D_800E7CC0, D_800E7CC4;
extern s32 D_800E7C98[];
extern s32 D_800E9F70, D_800DF1D4, D_800DF1D8, D_800E8210, D_800E79CC, D_800E74C4;
extern s32 D_800E6B68[], D_800EA308[];
s32 func_8001C580(void);
void func_800B807C(s32, s32);
void func_800BBAC8(s32);
void func_800BB6E8(s32);
s32 func_800AA1E0(s32, s32, s32, s32);

s32 func_800BBEB8(s32 n) {
    u16 m = D_8007EF30.mode;
    s32 h, r, i, j, q;
    s32 *ids;

    if ((m & 0x10) && n >= 6) {
        n = 10;
    }
    if (n >= 10) {
        goto fail;
    }
    h = (n - 2) / 2;
    if (D_8007E8C0[h] < 0) {
        goto fail;
    }
    D_800EA0AC = 0;
    D_800EA0A8 = 0;
    D_800E74BC = 0;
    D_800E74B8 = 0;
    D_800EA320 = 0;
    D_800DF1E0 = h;
    if (m & 0x60) {
        D_800DF1E8 = h & 2;
        if (D_8007E8C0[h + 1] >= 0) {
            D_800DF1E4 = 1;
            D_800E7CC0 = 1;
            D_800E7CC4 = 2;
        } else {
            D_800DF1E4 = 0;
            D_800E7CC0 = 0;
            D_800E7CC4 = -1;
        }
    } else if ((m & 0x10) && D_8007E8C0[h + 2] >= 0) {
        D_800DF1E8 = h & 1;
        D_800DF1E4 = 2;
        D_800E7CC0 = 1;
        D_800E7CC4 = 3;
    } else {
        D_800DF1E4 = 0;
        D_800E7CC0 = 0;
        D_800E7CC4 = -1;
        D_800DF1E8 = D_800DF1E0 & 1;
    }
    if (!((n - 2) & 1)) {
        D_800E7C98[0] = D_800E7C98[1] = D_800E7C98[2] = D_800E7C98[3] = -1;
        D_800E9F70 = D_8007EF30.f4;
        do {
            r = func_8001C580() % 6;
        } while ((D_800DF1D4 >> r) & 1);
        D_800DF1D4 |= 1 << r;
        func_800B807C(0, r + 1);
        do {
            j = func_8001C580() % 5;
        } while ((D_800DF1D8 >> j) & 1);
        D_800DF1D8 |= 1 << j;
        D_800E8210 = j;
        D_800E79CC = 0;
    } else {
        D_800E9F70 = -1;
        D_800E74C4 = 0;
        func_800B807C(1, 0xB);
        D_800E79CC = 0x100;
        func_800BBAC8(D_800DF1E8);
        D_800E7C98[0] = D_800E7C98[1] = D_800E7C98[2] = D_800E7C98[3] = -1;
        ids = D_8007E228.ids;
        for (i = 0; i < D_800DF1E0; i++) {
            D_800E7C98[3 - i] = ids[i];
            D_800E6B68[j = 3 - i] = func_800AA1E0(-1, ids[i], D_8007E8C0[0x1C + i] | 0x80, 6);
            if (i == 4) {
                j = 0xA;
            } else if (D_8007EF30.mode & 0x80) {
                j = i + 6;
            } else if (D_8007EF30.mode & 0x10) {
                j = i;
            } else {
                j = i + 2;
            }
            D_800EA308[3 - i] = j;
        }
        if (D_800DF1E4 == 2 && D_800DF1E0 != 0) {
            D_800E6B68[3 - i] = 0;
            D_800EA308[3 - i] = 0xA;
            D_800E7C98[3 - i] = D_8007E8B8;
        }
    }
    func_800BB6E8(1);
    goto end;
fail:
    n = 10;
end:
    return n;
}
