/* @header
 * func_800BAC58
 * VRAM 0x800BAC58 | ROM 0x673C8 | size 0x98
 * asm: asm/nonmatchings/code_80090000/func_800BAC58.s
 */
#include "common.h"

extern u8 *D_800DCFB8;

void func_800BAC58(u8 *o, s32 i) {
    u16 *p = (u16 *)(D_800DCFB8 + (i * 6 + 0x22));
    p[0] = (o[0] & 0xF) | ((o[1] & 0xF) << 4) | ((o[2] & 0xF) << 8) | ((o[3] & 0xF) << 12);
    p[1] = (o[4] & 0xF) | ((o[5] & 0xF) << 4) | ((o[6] & 0xF) << 8) | ((o[7] & 0xF) << 12);
}
