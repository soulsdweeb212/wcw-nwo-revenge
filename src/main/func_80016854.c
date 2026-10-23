#include "common.h"

s8 func_80015B84(u8);

/* Decode a signed byte into arg0+0xD9, then add the next byte to it. */
u8 *func_80016804(u8 *arg0, u8 *arg1) {
    s8 v = func_80015B84(*arg1++);
    *(s8 *)(arg0 + 0xD9) = v;
    v += *arg1++;
    *(s8 *)(arg0 + 0xD9) = v;
    return arg1;
}

/* Decode a signed byte into arg0+0xDC, then add the next byte to it. */
u8 *func_80016854(u8 *arg0, u8 *arg1) {
    s8 v = func_80015B84(*arg1++);
    *(s8 *)(arg0 + 0xDC) = v;
    v += *arg1++;
    *(s8 *)(arg0 + 0xDC) = v;
    return arg1;
}

/* Decode a signed byte into arg0+0xDD, then add the next byte to it. */
u8 *func_800168A4(u8 *arg0, u8 *arg1) {
    s8 v = func_80015B84(*arg1++);
    *(s8 *)(arg0 + 0xDD) = v;
    v += *arg1++;
    *(s8 *)(arg0 + 0xDD) = v;
    return arg1;
}

extern f64 D_8003B3F0;

/* Square arg0's +0x90 float into +0x38 and scale the next byte into +0x8C. */
void *func_800169D4(void *arg0, u8 *arg1) {
    f32 v = *(f32 *)((u8 *)arg0 + 0x90);
    *(f32 *)((u8 *)arg0 + 0x38) = v * v;
    *(f32 *)((u8 *)arg0 + 0x8C) = (f32)((f64)(f32)*arg1 * D_8003B3F0);
    return arg1 + 1;
}
