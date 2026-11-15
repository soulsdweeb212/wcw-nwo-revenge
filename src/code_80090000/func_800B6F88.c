/* @header
 * func_800B6F88
 * VRAM 0x800B6F88 | ROM 0x636F8 | size 0x58
 * asm: asm/nonmatchings/code_80090000/func_800B6F88.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port_decls.h declares func_800B600C */
u8 *func_800B600C(u8 *, s32);
#endif

static inline u8 *hdr(u8 *a, u8 **b, u8 **c) {
    u8 *p = a + 0x10;
    *c = p;
    p += *(u16 *)(a + 0xA) * 2;
    *b = p;
    return a;
}

#ifdef TARGET_PC
/* PC: the picture's key is a MenuKey (port.h), as func_800B600C takes it (port_decls.h); its callers (func_80097E1C,
 * func_8009EC58, func_800A8BB0) pass resource ids, for which func_800B600C hands back the picture's heap block. */
u8 *func_800B6F88(MenuKey a, u8 **b, u8 **c) {
#else
u8 *func_800B6F88(u8 *a, u8 **b, u8 **c) {
#endif
    u8 *v = func_800B600C(a, 0);
    if (v == 0) {
        return 0;
    }
    return hdr(v, b, c);
}
