/* @header
 * func_8000D210
 * VRAM 0x8000D210 | ROM 0xDE10 | size 0x28
 * asm: asm/nonmatchings/main/func_8000D210.s
 */
#include "common.h"

s32 func_8000C1B8(s16, s16);

/* Thin wrapper forwarding both arguments to func_8000C1B8. */
void func_8000D210(s16 arg0, s16 arg1) {
    func_8000C1B8(arg0, arg1);
}
