/* @header
 * func_800BF018
 * VRAM 0x800BF018 | ROM 0xB24B8 | size 0x138
 * asm: asm/nonmatchings/code_800BBA00/func_800BF018.s
 */
#include "common.h"

extern f64 D_800E5868;
extern f64 D_800E5870;
extern f64 D_800E5878;

/* Directional boundary test for w by side w->dirIndex: for sides 0/2 compares
 * the pelvis X (jointA[1].x) against the low/high f64 thresholds selected by
 * mask bits 0x200/0x100; for sides 1/3 compares the pelvis Z (jointA[1].z)
 * (bits 0x400/0x800). When a bound is crossed it runs func_800BED3C(w, other);
 * if that returns a mask intersecting the request it reports 2, otherwise 1,
 * else 0. */
s32 func_800BF018(Wrestler *w, Wrestler *other, u32 mask) {
    s32 flag = 0, result;
    u32 m = mask;
    s16 side = w->dirIndex;

    switch (side) {
    case 0:
    case 2:
        if ((m & 0x200) && (f64)w->jointA[1].x < D_800E5868) {
            flag = 1;
            break;
        }
        if ((m & 0x100) && D_800E5878 < (f64)w->jointA[1].x) {
            flag = 1;
        }
        break;
    case 1:
    case 3:
        if ((m & 0x400) && (f64)w->jointA[1].z < D_800E5870) {
            flag = 1;
            break;
        }
        if ((m & 0x800) && D_800E5878 < (f64)w->jointA[1].z) {
            flag = 1;
        }
        break;
    }

    result = flag;
    if (result == 0) {
        result = 0;
    } else {
        result = func_800BED3C(w, other, mask);
        if (m & result & 0xFFFF) {
            return 2;
        }
        return 1;
    }
    return result;
}
