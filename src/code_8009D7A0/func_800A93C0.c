#include "common.h"

extern u8 D_800FADCF;
extern u8 D_800F9D12[], D_800F9D1A[];

s32 func_800A93C0(void) {
    s16 i;
    s32 off;

    if (D_800FADCF & 0x40) {
        return 1;
    }
    for (i = 0; i < 4; i++) {
        off = i * 0x3B0;
        if (*(s16 *)(D_800F9D12 + off) != -1) {
            if (*(s16 *)(D_800F9D1A + off) == 0x8F || (*(u64 *)(D_800F9D30 + off) & 0x10)) {
                return 1;
            }
        }
    }
    return 0;
}
