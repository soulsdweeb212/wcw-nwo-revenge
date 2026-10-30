/* @header
 * func_80003418
 * VRAM 0x80003418 | ROM 0x4018 | size 0x4C
 * asm: asm/nonmatchings/main/func_80003418.s
 */
#include "common.h"

s32 func_800137F0(s32, s16);
extern s16 D_800482D8;

/* Set the global volume byte from arg0 (a nonnegative s8): store arg0<<8 in
 * D_800482D8, OR in 0xFF when nonzero, and forward to func_800137F0. */
void func_80003418(s8 arg0) {
    s16 t;

    if (arg0 >= 0) {
        t = arg0 << 8;
        D_800482D8 = t;
        if (t != 0) {
            D_800482D8 = t | 0xFF;
        }
        func_800137F0(2, D_800482D8);
    }
}
