/* @header
 * func_800AA070
 * VRAM 0x800AA070 | ROM 0x567E0 | size 0x34
 * asm: asm/nonmatchings/code_80090000/func_800AA070.s
 */
#include "common.h"

extern s32 D_8007E228[];
extern s32 D_8007E8C0[];
#ifndef TARGET_PC /* on PC, port_decls.h declares func_8002AD04, which returns the name record's address */
void func_8002AD04(s32, s32);
#endif

#ifdef TARGET_PC
/* PC: the N64 definition is void, but it ends with its call of func_8002AD04, so that call's result, the address of
 * the name record (see func_8002AD04.c), is still in v0 when it returns, and its callers use it: func_8009F2F8 hands
 * it to func_80095884 as a name, func_8009FE3C to func_800A3E00. On PC nothing carries a result that a function does
 * not return, so the PC definition returns that address. */
u8 *func_800AA070(s32 i) {
    return func_8002AD04(D_8007E228[i + 0x1A2], D_8007E8C0[i + 0x1C]);
}
#else
void func_800AA070(s32 i) {
    func_8002AD04(D_8007E228[i + 0x1A2], D_8007E8C0[i + 0x1C]);
}
#endif
