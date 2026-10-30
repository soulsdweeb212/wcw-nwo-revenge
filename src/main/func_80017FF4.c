/* @header
 * func_80017FF4
 * VRAM 0x80017FF4 | ROM 0x18BF4 | size 0x50
 * asm: asm/nonmatchings/main/func_80017FF4.s
 */
#include "common.h"

extern void *D_80036F54;
extern f64 D_8003B410;
extern f64 D_8003B418;

/* Scale arg0 by D_80036F54's +0x40 field and convert it to a fixed-point value. */
s32 func_80017FF4(s32 arg0) {
    return (s32) (f32) (((f64) ((f32) arg0 * (f32) *(s32 *)((s8 *)D_80036F54 + 0x40)) / D_8003B410) + D_8003B418);
}
