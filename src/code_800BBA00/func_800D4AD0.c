/* @header
 * func_800D4AD0
 * VRAM 0x800D4AD0 | ROM 0xC7F70 | size 0x40
 * asm: asm/nonmatchings/code_800BBA00/func_800D4AD0.s
 */
#include "common.h"

s32 func_800D35B0(s32, s32);
s32 func_800D4B10(Wrestler *);

/* Finish the current animation: copy anim.endPose into pose, add anim.headingDelta to heading (wrapped to
 * -0x800..0x7FF by func_800D35B0), then apply anim.endZone through func_800D4B10. */
void func_800D4AD0(Wrestler *w) {
    w->pose = (u8)w->anim.endPose;
    w->heading = func_800D35B0(w->heading, w->anim.headingDelta);
    func_800D4B10(w);
}
