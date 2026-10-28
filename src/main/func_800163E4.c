#include "common.h"

extern f64 D_8003B3C8;
extern f64 D_8003B3D0;
extern f64 D_8003B3D8;
extern f64 D_8003B3E0;

/* Decode a two-byte (big-endian) release rate into +0xD2. */
u8 *func_800163E4(u8 *arg0, u8 *arg1) {
    u8 hi;
    u8 lo;

    hi = *arg1;
    arg1++;
    lo = *arg1;
    *(s16 *)(arg0 + 0xD4) = 0;
    *(s16 *)(arg0 + 0xD2) = lo | (hi << 8);
    return arg1 + 1;
}
