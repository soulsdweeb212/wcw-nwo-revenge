/* @header
 * func_800A8D14
 * VRAM 0x800A8D14 | ROM 0x9C1B4 | size 0x78
 * asm: asm/nonmatchings/code_8009D7A0/func_800A8D14.s
 */
#include "common.h"

extern u8 D_80064AD8[];

/* Returns the entity's animation id derived from its +0x386 base, the +0x38C
 * index and the packed 2-bit table entry for the attachment's group. */
s16 func_800A8D14(void *arg0, void *arg1) {
    s8 *rec;
    s16 i;
    u8 *base;
    u8 *p;
    s16 v;

    rec = *(s8 **)((u8 *)arg1 + 0x364);
    i = *(s16 *)((u8 *)arg0 + 0x38C);
    base = &D_80064AD8[8];
    p = base + rec[0x20] * 400;
    v = ((p[i / 4] >> ((i & 3) * 2)) & 3) + 1;
    return *(u16 *)((u8 *)arg0 + 0x386) + v;
}
