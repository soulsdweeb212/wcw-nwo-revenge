/* @header
 * func_800996B0
 * VRAM 0x800996B0 | ROM 0x45E20 | size 0x54
 * asm: asm/nonmatchings/code_80090000/func_800996B0.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the cursor is a Gfx ** (port.h's 16-byte Gfx, which func_800B75D4 writes), and func_80099734 returns the address
 * of the message's name, which func_800B75D4 takes as a key of the resource-name cache (port_decls.h, port.h's
 * MENU_KEY_NAME). Id 0x121 has no name: the N64 then passes 0, a number, for which func_800B75D4 draws nothing, and so
 * does the PC. The result is func_800B75D4's, the cache entry's address, a pointer. */
void *func_800996B0(Gfx **arg0, s32 arg1, s32 arg2) {
    Gfx *cur;
    u8 *name;
    void *ret;

    cur = *arg0;
    name = func_80099734(arg1);
    ret = func_800B75D4(&cur, name != NULL ? MENU_KEY_NAME(name) : 0, arg2);
    *arg0 = cur;
    return ret;
}
#else
s32 func_80099734(s32);
s32 func_800B75D4(s32 *, s32, s32);

/* Append an entry described by (func_80099734(arg1), arg2) to the display list in
 * *arg0, updating *arg0 and returning the helper's result. */
s32 func_800996B0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 cur;
    s32 ret;

    cur = *arg0;
    ret = func_800B75D4(&cur, func_80099734(arg1), arg2);
    *arg0 = cur;
    return ret;
}
#endif
