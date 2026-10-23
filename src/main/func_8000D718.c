#include "common.h"

s32 func_8000520C(s32, s32);

/* Apply func_8000520C to 20 record pairs (destination stride 0xDC, source stride
 * 0x2C). */
void func_8000D718(s32 dst, s32 src) {
    s32 i;
    s32 s;
    u32 n;

    n = 0;
    s = src;
    i = dst;
    do {
        func_8000520C(i, s);
        s += 0x2C;
        n += 1;
        i += 0xDC;
    } while (n < 0x14U);
}
