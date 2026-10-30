/* @header
 * func_800A7C40
 * VRAM 0x800A7C40 | ROM 0x9B0E0 | size 0xDC
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7C40.s
 */
#include "common.h"

extern u8 D_80075468[];
void unpackAnimationParameters(void *, void *);

/* Set entity p's animation id (+0x384) and reaction id (+0x386), then unpack
 * the animation parameters for the chosen model (D_80075468 + 0x10 + id*0x1A30)
 * and reaction into p+0x38C. For reactions below 0xEF, set or clear the
 * 0x4000000000000000 flag from bit 0x8000 of p+0x3AC. */
void func_800A7C40(u8 *p, s8 arg1, s16 arg2) {
    s32 idx;
    u8 *tbl;

    *(volatile u8 *)(p + 0x384) = arg1;
    idx = *(s8 *)(p + 0x384);
    *(s16 *)(p + 0x386) = arg2;
    tbl = &D_80075468[0x10] + idx * 0x1A30;
    unpackAnimationParameters(p + 0x38C, tbl + arg2 * 0x18);
    if (arg2 < 0xEF) {
        if (*(s32 *)(p + 0x3AC) & 0x8000)
            *(u64 *)(p + 0x20) |= 0x4000000000000000ULL;
        else
            *(u64 *)(p + 0x20) &= ~0x4000000000000000ULL;
    }
}
