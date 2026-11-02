/* @header
 * func_800B1A30
 * VRAM 0x800B1A30 | ROM 0x5E1A0 | size 0x124
 * asm: asm/nonmatchings/code_80090000/func_800B1A30.s
 */
#include "common.h"

typedef struct { u32 a; u32 b; } P;
extern P *D_800E7CB0;
extern u64 D_800DC860[];
extern u16 D_800CD820[];

void func_800B1A30(P *arg) {
    s32 i, k;
    u64 *a = D_800DC860;
    D_800E7CB0 = arg;
    for (i = 0; i < 6; i++) {
        a[i] = 0;
        for (k = D_800CD820[i]; k < D_800CD820[i + 1]; k++) {
            if (i == 2) {
                a[2] += arg[k].b;
            } else {
                a[i] += arg[k].a;
            }
        }
    }
}
