/* @header
 * func_800D4CC4
 * VRAM 0x800D4CC4 | ROM 0xC8164 | size 0x80
 * asm: asm/nonmatchings/code_800BBA00/func_800D4CC4.s
 */
#include "common.h"

/* Applies the pose the animation ends in (anim.endPose): odd poses 7..31 clear
 * and even poses 8..32 set flags bit 0x200000. Returns 1 when the end pose is
 * >= 7 (a down pose). */
s32 func_800D4CC4(Wrestler *w) {
    switch (w->anim.endPose) {
    case 7:
    case 9:
    case 11:
    case 13:
    case 15:
    case 17:
    case 19:
    case 21:
    case 23:
    case 25:
    case 27:
    case 29:
    case 31:
        w->flags &= ~0x200000;
        break;
    case 8:
    case 10:
    case 12:
    case 14:
    case 16:
    case 18:
    case 20:
    case 22:
    case 24:
    case 26:
    case 28:
    case 30:
    case 32:
        w->flags |= 0x200000;
        break;
    }
    return w->anim.endPose >= 7;
}
