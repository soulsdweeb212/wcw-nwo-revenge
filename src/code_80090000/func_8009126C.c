/* @header
 * func_8009126C
 * VRAM 0x8009126C | ROM 0x3D9DC | size 0x28
 * asm: asm/nonmatchings/code_80090000/func_8009126C.s
 */
#include "common.h"

extern u8 D_800C5D10[];

/* Append a G_LOAD_UCODE display-list command (0xDE000000 + ucode pointer) to *arg0. */
void func_8009126C(u32 **arg0) {
    u32 *p = *arg0;
    u32 *start = p;
    p += 2;
    start[0] = 0xDE000000;
    start[1] = (u32)D_800C5D10 + 0x48;
    *arg0 = p;
}
