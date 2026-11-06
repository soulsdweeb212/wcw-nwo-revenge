/* @header
 * func_800A7240
 * VRAM 0x800A7240 | ROM 0x9A6E0 | size 0xBC
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7240.s
 */
#include "common.h"

s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);

/* Turns the wrestler's heading toward target: if the remaining delta is
 * within step it snaps to target and raises the flags in setFlags, returning 1;
 * otherwise it steps the heading by step in the delta's direction and returns 0. */
s32 func_800A7240(Wrestler *w, s32 target, s32 step, u64 setFlags) {
    s32 t;

    t = func_800D3684(target, w->heading);
    if (func_800D3550(t) < step) {
        w->heading = target;
        w->flags |= setFlags;
        return 1;
    }
    if (t >= 0)
        t = step;
    else
        t = -step;
    w->heading = func_800D35B0(w->heading, t);
    return 0;
}
