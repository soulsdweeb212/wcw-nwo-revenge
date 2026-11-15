/* @header
 * func_80099734
 * VRAM 0x80099734 | ROM 0x45EA4 | size 0x14
 * asm: asm/nonmatchings/code_80090000/func_80099734.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the result is the address of the name of message id arg0, so a pointer (port_decls.h). The N64 reads a word
 * at D_800C8D84 + 0x1DC + arg0 * 4; the ids its callers pass, 0x122 to 0x134, reach the table of 19 name addresses
 * at 0x800C93E8 (up to D_800C9434), which has no label of its own, so the PC names it by its address and reads it as
 * pointers. The word before it, which id 0x121 reaches (func_8009FE3C draws ids from 0x121), is 0: no name. Any other
 * id reads words that are not addresses on the N64, so the PC stops there. */
extern u8 *D_800C93E8[19];

u8 *func_80099734(s32 arg0) {
    if (arg0 == 0x121) {
        return NULL;
    }
    if ((u32)(arg0 - 0x122) >= 19) {
        port_fatal("func_80099734: message id 0x%X has no name", arg0);
    }
    return D_800C93E8[arg0 - 0x122];
}
#else
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
#endif
