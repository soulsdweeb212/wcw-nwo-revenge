/* @header
 * func_800B1B54
 * VRAM 0x800B1B54 | ROM 0x5E2C4 | size 0x1B0
 * asm: asm/nonmatchings/code_80090000/func_800B1B54.s
 */
#include "common.h"


extern s32 D_800EA0B8;
extern s32 D_800E9F98[];
u64 func_80028860(u64, u64);

s32 func_800B1B54(s64 *a, s32 n) {
    s32 i, t, sum, b;

    D_800EA0B8 = n;
    t = 0;
    for (i = 0; i < n; i++) {
        t += a[i];
    }
    if (t == 0) {
        for (i = 0; i < n; i++) {
            D_800E9F98[i] = 0;
        }
    } else {
        sum = 0;
        for (i = 0; i < n; i++) {
            D_800E9F98[i] = func_80028860(a[i] * 1000, t);
            sum += D_800E9F98[i];
        }
        b = 0;
        for (i = 0; i < n; i++) {
            if (D_800E9F98[i] > D_800E9F98[b]) {
                b = i;
            }
        }
        D_800E9F98[b] += 1000 - sum;
    }
    return t;
}
