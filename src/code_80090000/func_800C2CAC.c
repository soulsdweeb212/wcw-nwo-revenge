/* @header
 * func_800C2CAC
 * VRAM 0x800C2CAC | ROM 0x6F41C | size 0x30
 * asm: asm/nonmatchings/code_80090000/func_800C2CAC.s
 */
#include "common.h"

extern s32 D_800E79B8;

s16 func_800C2CAC(s32 arg0) {
    return (*(s16 *)((u8 *)((arg0 * 0x6D0) + D_800E79B8) + 0x6B6));
}
