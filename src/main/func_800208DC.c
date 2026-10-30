/* @header
 * func_800208DC
 * VRAM 0x800208DC | ROM 0x214DC | size 0x4C
 * asm: asm/nonmatchings/main/func_800208DC.s
 */
#include "common.h"

extern f64 D_8003B8C0;
extern f64 D_8003B8C8;

/* Scales arg1 by the object's +0x44 rate, applies the D_8003B8C0/B8C8 bias and
 * truncates the result to a 16-byte multiple. */
s32 func_800208DC(void *arg0, s32 arg1) {
    return (s32) (f32) (((f64) ((f32) arg1 * (f32) *(s32 *)((u8 *)arg0 + 0x44)) / D_8003B8C0) + D_8003B8C8) & ~0xF;
}
