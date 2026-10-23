#include "common.h"

extern s8 D_800484F4[];
extern s8 D_800484F8[];
extern s8 D_800484FC[];

/* Absolute value of a float. */
f32 func_80003CF0(f32 x) {
    if (x >= 0.0) {
        return x;
    }
    return -x;
}

/* Marks slot i as active. */
void func_8000439C(s16 i) {
    if (D_800484F4[i] == 0) {
        D_800484F4[i] = 1;
    }
}

/* Clears slot i and invalidates its value. */
void func_800043CC(s16 i) {
    if (D_800484F4[i] == 1) {
        D_800484F4[i] = 0;
        D_800484FC[i] = -1;
    }
}

/* Resets the four slots to arg0 with an invalid value. */
void func_8000440C(s8 arg0) {
    u32 i;
    for (i = 0; i < 4; i++) {
        D_800484F4[i] = 0;
        D_800484F8[i] = arg0;
        D_800484FC[i] = -1;
    }
}
