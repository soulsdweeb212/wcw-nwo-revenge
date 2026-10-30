/* @header
 * func_8000333C
 * VRAM 0x8000333C | ROM 0x3F3C | size 0x20
 * asm: asm/nonmatchings/main/func_8000333C.s
 */
#include "common.h"

s32 func_8001613C(s32);

/* Enable/disable audio output from whether arg0 is zero. */
void func_8000333C(s32 arg0) {
    func_8001613C((arg0 << 0x10) == 0);
}
