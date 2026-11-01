/* @header
 * func_800996A0
 * VRAM 0x800996A0 | ROM 0x45E10 | size 0x10
 * asm: asm/nonmatchings/code_80090000/func_800996A0.s
 */
#include "common.h"

extern u8 D_800C9014[];
extern u8 D_800C8D84[];
extern u8 D_800C94CC[];
s32 func_80099734(s32);
s32 func_800B75D4(s32 *, s32, s32);
u8 *func_80028D18(s32);
u8 *func_80029A24(u8 *, s32, s32);

u8 func_800996A0(s32 arg0) {
    return D_800C9014[0x49C + arg0];
}
