/* @header
 * func_8000440C
 * VRAM 0x8000440C | ROM 0x500C | size 0x44
 * asm: asm/nonmatchings/main/func_8000440C.s
 */
#include "common.h"

extern s8 D_800484F4[];
extern s8 D_800484F8[];
extern s8 D_800484FC[];

/* Initialize the four slots with the given kind byte. */
void func_8000440C(s8 arg0) {
    u32 i;
    for (i = 0; i < 4; i++) {
        D_800484F4[i] = 0;
        D_800484F8[i] = arg0;
        D_800484FC[i] = -1;
    }
}
