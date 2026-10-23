#include "common.h"

extern f64 D_800E6B78;

/* Convert radians arg0 to a 4096-unit-turn angle. */
s32 func_800D35F4(f32 arg0) {
    return (s32) ((f64) arg0 * D_800E6B78);
}
