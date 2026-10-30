/* @header
 * func_800A9488
 * VRAM 0x800A9488 | ROM 0x9C928 | size 0x2C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A9488.s
 */
#include "common.h"

/* When arg1's state (+0xA) is 0x2C or 0x2D, advance its timer (+0x18) by arg0's
 * +0x36C amount. */
void func_800A9488(void *arg0, void *arg1) {
    if ((u32) (*(u16 *)((u8 *)arg1 + 0xA) - 0x2C) < 2U) {
        *(u16 *)((u8 *)arg1 + 0x18) = (u16) (*(u16 *)((u8 *)arg1 + 0x18) + *(u8 *)((u8 *)arg0 + 0x36C));
    }
}
