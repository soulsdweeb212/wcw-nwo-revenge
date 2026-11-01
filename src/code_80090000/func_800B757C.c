/* @header
 * func_800B757C
 * VRAM 0x800B757C | ROM 0x63CEC | size 0x28
 * asm: asm/nonmatchings/code_80090000/func_800B757C.s
 */
#include "common.h"

extern u8 D_D28A8[];

void func_800B757C(u32 **dl) {
    u32 *g = *dl;
    u32 *t = g;
    g += 2;
    t[0] = 0xDE000000;
    t[1] = (u32)D_D28A8;
    *dl = g;
}
