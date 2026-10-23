#include "common.h"

extern s16 D_800604E4;
extern s16 D_800604E6;

/* Set the global volume pair selected by mask arg0 (bit 0 = D_800604E4, bit 1 =
 * D_800604E6) to arg1. */
void func_800137F0(s32 arg0, s16 arg1) {
    if (arg0 & 1) {
        D_800604E4 = arg1;
    }
    if (arg0 & 2) {
        D_800604E6 = arg1;
    }
}
