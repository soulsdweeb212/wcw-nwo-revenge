/* @header
 * func_800A9F30
 * VRAM 0x800A9F30 | ROM 0x566A0 | size 0x34
 * asm: asm/nonmatchings/code_80090000/func_800A9F30.s
 */
#include "common.h"

extern u8 D_8007EF30[];
#define F(t, o, i) (*(t *)(D_8007EF30 + (o) + ((i) << 4)))

#ifndef TARGET_PC /* on PC, port_decls.h declares func_8002AD34 */
void func_8002AD34(s32, s32);
#endif

#ifdef TARGET_PC
/* PC: the result is func_8002AD34's, the address of a name, which func_800A8140 hands to func_800B75D4. The N64
 * function leaves that address in the result register without a return statement (func_800A8140 declares it
 * returning an s32 and uses it); on PC it returns it, as the pointer it is. */
u8 *func_800A9F30(s32 i) {
    return func_8002AD34(F(s16, 0x4E, i), F(u8, 0x50, i));
}
#else
void func_800A9F30(s32 i) {
    func_8002AD34(F(s16, 0x4E, i), F(u8, 0x50, i));
}
#endif
