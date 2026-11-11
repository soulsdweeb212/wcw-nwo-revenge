/* @header
 * func_800D65D0
 * VRAM 0x800D65D0 | ROM 0xC9A70 | size 0x40
 * asm: asm/nonmatchings/code_800BBA00/func_800D65D0.s
 */
#include "common.h"

extern u32 D_800FABD8;
extern u16 D_800E3F84[];
extern u16 D_800E3F8C[];
extern u8 D_80030560[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007C438; not used here */
extern u8 D_8007C438[];
#endif

/* Classify the wrestler's ringSide against mask arg1: 1 when D_800E3F84[ringSide]
 * shares a bit with it, else 2 when D_800E3F8C[ringSide] does, else 0. */
s32 func_800D65D0(Wrestler *w, s32 arg1) {
    s32 idx = w->ringSide;

    if (D_800E3F84[idx] & arg1) {
        return 1;
    }
    return ((D_800E3F8C[idx] & arg1) != 0) * 2;
}
