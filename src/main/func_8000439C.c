/* @header
 * func_8000439C
 * VRAM 0x8000439C | ROM 0x4F9C | size 0x30
 * asm: asm/nonmatchings/main/func_8000439C.s
 */
#include "common.h"

extern s8 D_800484F4[];
extern s8 D_800484F8[];
extern s8 D_800484FC[];

/* Marks slot i as active. */
void func_8000439C(s16 i) {
    if (D_800484F4[i] == 0) {
        D_800484F4[i] = 1;
    }
}
