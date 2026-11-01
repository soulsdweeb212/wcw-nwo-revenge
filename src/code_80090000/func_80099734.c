/* @header
 * func_80099734
 * VRAM 0x80099734 | ROM 0x45EA4 | size 0x14
 * asm: asm/nonmatchings/code_80090000/func_80099734.s
 */
#include "common.h"

extern u8 D_800C9014[];
extern u8 D_800C8D84[];
extern u8 D_800C94CC[];
s32 func_80099734(s32);
s32 func_800B75D4(s32 *, s32, s32);
u8 *func_80028D18(s32);
u8 *func_80029A24(u8 *, s32, s32);

s32 func_80099734(s32 arg0) {
    return *(s32 *)(D_800C8D84 + 0x1DC + (arg0 << 2));
}
