/* @header
 * func_800B5FD0
 * VRAM 0x800B5FD0 | ROM 0x62740 | size 0x3C
 * asm: asm/nonmatchings/code_80090000/func_800B5FD0.s
 */
#include "common.h"

typedef struct { s32 a; s32 b; s32 c; s32 d; } N;
extern N D_800E6BA0[];

void func_800B5FD0(void) {
    s32 i;
    N *p;
    for (i = 0, p = D_800E6BA0; i < 0x80; i++, p++) {
        p->a = -1;
        p->d = 0;
        p->b = 0;
    }
}
