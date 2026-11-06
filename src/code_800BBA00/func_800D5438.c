/* @header
 * func_800D5438
 * VRAM 0x800D5438 | ROM 0xC88D8 | size 0x54
 * asm: asm/nonmatchings/code_800BBA00/func_800D5438.s
 */
#include "common.h"

extern u8 D_80030560[];
extern u8 D_8007C438[];

/* Looks up an animation id for the current move: reads the D_80030560 table
 * entry at moveId, adds arg1, indexes the moveOwnerId row (0x600 bytes per
 * wrestler, at D_8007C438 + 0x180) with it and adds the base 0x110B. */
s16 func_800D5438(Wrestler *w, s32 arg1) {
    s32 idx = w->moveId;
    s32 row = w->moveOwnerId;
    u16 t = ((u16 *)(D_80030560 + 0x10))[0 + idx];
    s32 off = (s16)(t + arg1);
    u16 *p = (u16 *)(D_8007C438 + 0x180 + row * 0x600);
    return p[off] + 0x110B;
}
