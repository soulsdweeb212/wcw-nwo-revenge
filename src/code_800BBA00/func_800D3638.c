/* @header
 * func_800D3638
 * VRAM 0x800D3638 | ROM 0xC6AD8 | size 0x18
 * asm: asm/nonmatchings/code_800BBA00/func_800D3638.s
 */
#include "common.h"

s32 func_800D3638(s32 arg0) {
    s32 v = arg0;
    v += 0x1100;
    if (v < 0) {
        v += 0x1FF;
    }
    return (v >> 9) & 7;
}
