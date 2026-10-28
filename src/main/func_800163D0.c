#include "common.h"

extern f64 D_8003B3C8;
extern f64 D_8003B3D0;
extern f64 D_8003B3D8;
extern f64 D_8003B3E0;

u8 *func_800163D0(u8 *arg0, u8 *arg1) {
    u8 v;

    v = *arg1;
    *(s16 *)(arg0 + 0xD2) = 0;
    *(s16 *)(arg0 + 0xD4) = v;
    return arg1 + 1;
}
