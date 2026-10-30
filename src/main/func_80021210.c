/* @header
 * func_80021210
 * VRAM 0x80021210 | ROM 0x21E10 | size 0x20
 * asm: asm/nonmatchings/main/func_80021210.s
 */
#include "common.h"

s32 func_800213CC(void *, s32);

/* Build the RDP command for arg0 into a scratch local. */
void func_80021210(s32 arg0) {
    s32 sp10;

    func_800213CC(&sp10, arg0);
}
