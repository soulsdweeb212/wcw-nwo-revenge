/* @header
 * func_800B50CC
 * VRAM 0x800B50CC | ROM 0x6183C | size 0x50
 * asm: asm/nonmatchings/code_80090000/func_800B50CC.s
 */
#include "common.h"

typedef struct { u8 p[0xA]; u16 f; u8 q[0x13C]; } P;
extern u8 *D_800E9AA4;

void func_800B50CC(void) {
    u8 **pp = &D_800E9AA4;
    u8 *p = *pp;
    u16 *q;
    s32 i;
    p[0x16] = 0;
    *(s16 *)(p + 0x20) = 0x1000;
    *(s16 *)(p + 0x22) = 0;
    p[0xB9E] = 0;
    q = (u16 *)(*pp + 0x152);
    for (i = 1; i < 9; i++) {
        *q |= 0x20;
        q += 0xA4;
    }
}
