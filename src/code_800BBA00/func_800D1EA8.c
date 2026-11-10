/* @header
 * func_800D1EA8
 * VRAM 0x800D1EA8 | ROM 0xC5348 | size 0xA8
 * asm: asm/nonmatchings/code_800BBA00/func_800D1EA8.s
 */
#include "common.h"

/* Push w and the opponent (called with D_800FAF5C, D_800F9B00) one step in the XZ plane. func_800D63F0 gives the
 * step length, w's walking speed from its profile tier (mode 2, doubled, when move.flags bit 0x10000 is set, else
 * mode 0; it also writes its X/Z speeds into xform, which func_800D37C0 overwrites). The direction is the angle
 * returned by func_800D6610 (from w's pelvis toward entry dirIndex of D_800E3C50) when move.flags bit 0x1000 is
 * set, else entry dirIndex of D_800E3C90; func_800D37C0 writes the XZ vector of that length and angle into xform,
 * and both records are translated by it. */
void translateEntityXZ(void *, void *);
f32 func_800D63F0(void *, void *, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares D_800E3C90, func_800D37C0 and func_800D6610 */
void *func_800D6610(void *, s16);
void func_800D37C0(void *, f32, void *);
extern void *D_800E3C90[];
#endif
void func_800D1EA8(Wrestler *w, Wrestler *opponent)
{
    f32 xform[4];
    f32 scale;
    scale = func_800D63F0(w, xform, ((w->move.flags >> 16) & 1) * 2);
    if (w->move.flags & 0x1000) {
        func_800D37C0(func_800D6610(w, w->dirIndex), scale, xform);
    } else {
        func_800D37C0(D_800E3C90[w->dirIndex], scale, xform);
    }
    translateEntityXZ(w, xform);
    translateEntityXZ(opponent, xform);
}
