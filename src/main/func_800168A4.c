#include "common.h"

s8 func_80015B84(u8);

/* Parses an envelope start level: seeds +0xD9 from a random byte and adds the
 * next byte. */
u8 *func_80016804(u8 *arg0, u8 *arg1) {
    s8 v = func_80015B84(*arg1++);
    *(s8 *)(arg0 + 0xD9) = v;
    v += *arg1++;
    *(s8 *)(arg0 + 0xD9) = v;
    return arg1;
}

/* Parses an envelope level: seeds +0xDC from a random byte and adds the next. */
u8 *func_80016854(u8 *arg0, u8 *arg1) {
    s8 v = func_80015B84(*arg1++);
    *(s8 *)(arg0 + 0xDC) = v;
    v += *arg1++;
    *(s8 *)(arg0 + 0xDC) = v;
    return arg1;
}

/* Parses an envelope level: seeds +0xDD from a random byte and adds the next. */
u8 *func_800168A4(u8 *arg0, u8 *arg1) {
    s8 v = func_80015B84(*arg1++);
    *(s8 *)(arg0 + 0xDD) = v;
    v += *arg1++;
    *(s8 *)(arg0 + 0xDD) = v;
    return arg1;
}

extern f64 D_8003B3F0;

/* Recomputes the voice's +0x38 from its +0x90 value and sets +0x8C from the
 * next envelope byte scaled by D_8003B3F0. */
void *func_800169D4(void *arg0, u8 *arg1) {
    f32 v = *(f32 *)((u8 *)arg0 + 0x90);
    *(f32 *)((u8 *)arg0 + 0x38) = v * v;
    *(f32 *)((u8 *)arg0 + 0x8C) = (f32)((f64)(f32)*arg1 * D_8003B3F0);
    return arg1 + 1;
}
