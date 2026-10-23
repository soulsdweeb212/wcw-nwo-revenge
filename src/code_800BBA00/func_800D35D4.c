#include "common.h"

extern f64 D_800E6B70;

/* Convert an angle in 4096-unit turns to radians. */
f32 func_800D35D4(s32 arg0) {
    return (f32) ((f64) arg0 * D_800E6B70);
}
