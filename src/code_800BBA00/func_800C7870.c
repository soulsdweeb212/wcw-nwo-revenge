/* @header
 * func_800C7870
 * VRAM 0x800C7870 | ROM 0xBAD10 | size 0x74
 * asm: asm/nonmatchings/code_800BBA00/func_800C7870.s
 */
#include "common.h"

typedef union { f32 f; s32 i; } NwFI;
typedef struct { NwFI e[4]; } NwV4;

f32 nw2Sqrtf(f32);
f32 func_80003A3C(f32, f32);

extern f64 D_800E6BA8;
extern f64 D_800E68D0;

/* Returns 1 when arg1's +0x37 bit0 is set, arg0/arg1 share the 0x40 flag and
 * arg2 is below D_800E68D0. */
s32 func_800C7870(u8 *arg0, u8 *arg1, f32 arg2) {
    if ((arg1[0x37] & 1) && ((*(u64 *)(arg0 + 0x20) & *(u64 *)(arg1 + 0x20)) & 0x40) &&
        ((f64)arg2 < D_800E68D0)) {
        return 1;
    }
    return 0;
}
