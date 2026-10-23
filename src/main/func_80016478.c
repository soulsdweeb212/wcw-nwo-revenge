#include "common.h"

extern f64 D_8003B3C8;
extern f64 D_8003B3D0;
extern f64 D_8003B3D8;
extern f64 D_8003B3E0;

/* Parses an ascending voice-envelope segment: stores the two level bytes and
 * derives the pitch (+0x34) and level (+0xFC) steps. */
u8 *func_80016408(u8 *arg0, u8 *arg1) {
    f32 a;
    f32 b;

    arg0[0xD6] = *arg1++;
    arg0[0xF5] = *arg1++;
    a = (f32)((f32)*arg1 / D_8003B3C8);
    b = (f32)(D_8003B3D0 / (f32)arg0[0xF5]);
    *(f32 *)(arg0 + 0x34) = a;
    *(f32 *)(arg0 + 0xFC) = b;
    return arg1 + 1;
}

/* Parses a descending voice-envelope segment (note the negated pitch step). */
u8 *func_80016478(u8 *arg0, u8 *arg1) {
    f32 a;
    f32 b;

    arg0[0xD6] = *arg1++;
    arg0[0xF5] = *arg1;
    b = (f32)(D_8003B3D8 / (f32)*(volatile u8 *)(arg0 + 0xF5));
    arg1++;
    a = (f32)(-(f32)*arg1 / D_8003B3E0);
    *(f32 *)(arg0 + 0xFC) = b;
    *(f32 *)(arg0 + 0x34) = a;
    return arg1 + 1;
}
