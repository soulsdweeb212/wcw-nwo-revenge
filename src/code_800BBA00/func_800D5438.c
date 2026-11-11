/* @header
 * func_800D5438
 * VRAM 0x800D5438 | ROM 0xC88D8 | size 0x54
 * asm: asm/nonmatchings/code_800BBA00/func_800D5438.s
 */
#include "common.h"

extern u8 D_80030560[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007C438; the rows read here are D_8007C5B8 there */
extern u8 D_8007C438[];
#endif

/* Looks up an animation id for the current move: reads the D_80030560 table
 * entry at moveId, adds arg1, indexes the moveOwnerId row (0x600 bytes per
 * wrestler, at D_8007C438 + 0x180) with it and adds the base 0x110B. */
s16 func_800D5438(Wrestler *w, s32 arg1) {
    s32 idx = w->moveId;
    s32 row = w->moveOwnerId;
    u16 t = ((u16 *)(D_80030560 + 0x10))[0 + idx];
    s32 off = (s16)(t + arg1);
#ifdef TARGET_PC
    /* PC: the wrestler's row of animation ids, D_8007C5B8[row] (port_decls.h); the N64 computes it as
     * D_8007C438 + 0x180 + row * 0x600. */
    u16 *p = D_8007C5B8[row];
#else
    u16 *p = (u16 *)(D_8007C438 + 0x180 + row * 0x600);
#endif
    return p[off] + 0x110B;
}
