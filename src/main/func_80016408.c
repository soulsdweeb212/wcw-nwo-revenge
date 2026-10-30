/* @header
 * func_80016408
 * VRAM 0x80016408 | ROM 0x17008 | size 0x70
 * asm: asm/nonmatchings/main/func_80016408.s
 */
#include "common.h"

extern f64 D_8003B3C8;
extern f64 D_8003B3D0;

/* Parses an ascending voice-envelope segment: stores the two level bytes and
 * derives the pitch (+0x34) and level (+0xFC) steps. */
u8 *func_80016408(u8 *arg0, u8 *arg1) {
    f32 a;
    f32 b;

    arg0[0xD6] = *arg1++;
    arg0[0xF5] = *arg1++;
    a = (f32)((f32)*arg1 / D_8003B3C8);
    b = (f32)(D_8003B3D0 / (f32)*(volatile u8 *)(arg0 + 0xF5));
    *(f32 *)(arg0 + 0x34) = a;
    *(f32 *)(arg0 + 0xFC) = b;
    return arg1 + 1;
}
