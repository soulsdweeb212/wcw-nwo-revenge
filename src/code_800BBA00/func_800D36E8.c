#include "common.h"

f32 func_80003A3C();
extern f64 D_800E6B80;

/* Convert the atan2-style result of func_80003A3C into a 4096-unit heading. */
s32 func_800D36E8(void) {
    return (s32) ((f64) func_80003A3C() * D_800E6B80);
}
