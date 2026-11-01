/* @header
 * func_800BACF0
 * VRAM 0x800BACF0 | ROM 0x67460 | size 0x90
 * asm: asm/nonmatchings/code_80090000/func_800BACF0.s
 */
#include "common.h"

extern u8 *D_800DCFB8;

void func_800BACF0(u8 *o, s32 i) {
    u16 *p = (u16 *)(D_800DCFB8 + (i * 6 + 0x22));
    o[0] = p[0] & 0xF;
    o[1] = (p[0] >> 4) & 0xF;
    o[2] = (p[0] >> 8) & 0xF;
    o[3] = p[0] >> 12;
    o[4] = p[1] & 0xF;
    o[5] = (p[1] >> 4) & 0xF;
    o[6] = (p[1] >> 8) & 0xF;
    o[7] = p[1] >> 12;
}
