/* @header
 * func_800996A0
 * VRAM 0x800996A0 | ROM 0x45E10 | size 0x10
 * asm: asm/nonmatchings/code_80090000/func_800996A0.s
 */
#include "common.h"

extern u8 D_800C9014[];
extern u8 D_800C8D84[];
extern u8 D_800C94CC[];
#ifdef TARGET_PC
/* PC: the byte table at 0x800C94B0, by its address: the N64 reaches it as D_800C9014 + 0x49C, past that label's own
 * data; named, it gets the width of bytes (tools/port_data.py), where the data before it is read as words. */
extern u8 D_800C94B0[];
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares func_80099734 and func_800B75D4 */
s32 func_80099734(s32);
s32 func_800B75D4(s32 *, s32, s32);
#endif
u8 *func_80028D18(s32);
u8 *func_80029A24(u8 *, s32, s32);

u8 func_800996A0(s32 arg0) {
#ifdef TARGET_PC
    return D_800C94B0[arg0];
#else
    return D_800C9014[0x49C + arg0];
#endif
}
