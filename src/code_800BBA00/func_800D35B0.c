/* @header
 * func_800D35B0
 * VRAM 0x800D35B0 | ROM 0xC6A50 | size 0x24
 * asm: asm/nonmatchings/code_800BBA00/func_800D35B0.s
 */
#include "common.h"

/* Sum angles arg0 + arg1, wrapped to [-0x800, 0x800]. */
s32 func_800D35B0(s32 arg0, s32 arg1) {
    s32 v = arg0 + arg1;
    s32 t = v;
    v &= 0xFFF;
    if (t & 0x800) {
        v |= 0xFFFFF000;
    }
    return v;
}
