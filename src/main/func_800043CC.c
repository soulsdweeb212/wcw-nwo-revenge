/* @header
 * func_800043CC
 * VRAM 0x800043CC | ROM 0x4FCC | size 0x40
 * asm: asm/nonmatchings/main/func_800043CC.s
 */
#include "common.h"

extern s8 D_800484F4[];
extern s8 D_800484F8[];
extern s8 D_800484FC[];

/* Deactivate slot i and invalidate its cached value. */
void func_800043CC(s16 i) {
    if (D_800484F4[i] == 1) {
        D_800484F4[i] = 0;
        D_800484FC[i] = -1;
    }
}
