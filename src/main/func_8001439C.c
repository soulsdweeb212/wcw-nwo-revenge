/* @header
 * func_8001439C
 * VRAM 0x8001439C | ROM 0x14F9C | size 0x7C
 * asm: asm/nonmatchings/main/func_8001439C.s
 */
#include "common.h"

s32 func_800202B0(s32, s32, void *, s32, s32);
extern u8 D_800604B8[];
extern s32 D_80060504;
extern s32 D_80060508;
extern s32 D_8006050C;
extern s32 D_80060510;

/* Allocates the audio command queue (arg0 entries clamped to 0x40..0x400,
 * 8 bytes each) and resets its read/write indices. */
void func_8001439C(s32 arg0) {
    s32 var_s0;

    var_s0 = arg0;
    if (var_s0 < 0x40) {
        var_s0 = 0x40;
    } else if (var_s0 >= 0x401) {
        var_s0 = 0x400;
    }
    D_80060510 = func_800202B0(0, 0, D_800604B8, 1, var_s0 * 8);
    D_8006050C = var_s0;
    D_80060508 = 0;
    D_80060504 = 0;
}
