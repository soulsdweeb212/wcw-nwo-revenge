/* @header
 * func_800B0524
 * VRAM 0x800B0524 | ROM 0x5CC94 | size 0x130
 * asm: asm/nonmatchings/code_80090000/func_800B0524.s
 */
#include "common.h"



extern u8 D_8007EF30[];
#ifndef TARGET_PC /* on PC, port_decls.h declares func_8002B5AC */
s32 func_8002B5AC(s32);
#endif
#ifdef TARGET_PC
/* PC: the types of func_8002B528's definition, which returns a u16: read as an s32, the PC result's upper bits would
 * be unset. */
u16 func_8002B528(s32);
#else
s32 func_8002B528(s32);
#endif
s32 func_800B0EC4(s32);
#define H(o) (*(u16 *)(D_8007EF30 + (o)))

s32 func_800B0524(s32 id) {
    u8 *t, *s;
    u16 f;

    if (func_8002B5AC(id) == 0) {
        return 0;
    }
    if (*(s16 *)(D_8007EF30 + 0x4E) == id) {
        return 0;
    }
    t = *(u8 **)(D_8007EF30 + 0x30);
    if (id == (*(u16 *)(D_8007EF30 + 0x4E + t[0] * 2 + 0x100) & 0xFFF)) {
        return 0;
    }
    if (func_800B0EC4(id) == 0) {
        return 0;
    }
    t = *(u8 **)(D_8007EF30 + 0x30);
    f = *(u16 *)(t + 6);
    s = *(u8 **)(t + 0x10);
    if (f & 0x20) {
        if (*(s16 *)(D_8007EF30 + 0x5E) == id) {
            return 0;
        }
        if (id == (H(0xCB0) & 0xFFF)) {
            return 0;
        }
        if (id == (H(0xCB2) & 0xFFF)) {
            return 0;
        }
        if (id != (H(0x158) & 0xFFF)) {
            return -1;
        }
zero:
        return 0;
    }
    if (id == (H(0xCA0) & 0xFFF)) {
        goto zero;
    }
    if (!(f & 0x2000)) {
        while (*s != 0) {
            if (id == func_8002B528(*s)) {
                goto zero;
            }
            s++;
        }
    }
    return -1;
}
