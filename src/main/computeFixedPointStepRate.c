#include "common.h"

extern f64 D_8003B4B8,D_8003B4C0,D_8003B4C8;

/* Computes a 16.16 fixed-point interpolation step from `start` to `end` over
 * `time` ticks: returns the signed step count and stores the fractional part in
 * *out. A zero time returns the saturated endpoints (0x7FFF/0xFFFF or 0/0). */
s16 computeFixedPointStepRate(f64 start, f64 end, s32 time, u16 *out) {
    f64 rate, value, fraction, scaled;
    s16 whole, carry, result;

    if (time == 0) {
        if (start <= end) {
            *out = 0xFFFF;
            return 0x7FFF;
        }
        *out = 0;
        return 0;
    }
    rate = D_8003B4B8 / time;
    if (end < D_8003B4B8) end = D_8003B4B8;
    if (start <= 0.0) start = D_8003B4B8;
    value = (end - start) * rate * D_8003B4C0;
    whole = value;
    fraction = value - whole + D_8003B4B8;
    carry = fraction;
    scaled = (fraction - carry) * D_8003B4C8;
    whole = whole - 1;
    result = whole + carry;
    *out = (u32)scaled;
    return result;
}
