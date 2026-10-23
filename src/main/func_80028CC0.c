#include "common.h"

/* Write `arg1` as a run of '#' bytes (at most 35 per entry) each followed by a hex
 * digit of the remainder; returns a pointer to the terminating NUL. */
u8 *func_80028CC0(u8 *arg0, s32 arg1) {
    u8 *q;
    s32 d;
    q = arg0;
    if (arg1 > 0) {
        do {
            d = arg1;
            if (d >= 0x23) d = 0x23;
            *q = 0x23;
            if (d < 0xA) arg0[1] = d + 0x30;
            else arg0[1] = d + 0x37;
            arg0 += 2;
            arg1 -= d;
            q += 2;
        } while (arg1 > 0);
    }
    *q = 0;
    return q;
}
