/* @header
 * func_800C2634
 * VRAM 0x800C2634 | ROM 0xB5AD4 | size 0x158
 * asm: asm/nonmatchings/code_800BBA00/func_800C2634.s
 */
#include "common.h"

s16 func_800D7B08(s32);
extern s32 D_800E3C90[];

/* Maps the input direction arg1 to a ring side (0..3); for the diagonal inputs
 * (func_800D7B08(arg1) != -1) moves to the next side when the angle between
 * D_800E3C90[side] and w->heading is in 0x201..0x5FF. Then, if hitInfo bit 12 is
 * set and that angle is below 0xE3, or bit 12 is clear and it is >= 0x71D, stores
 * the side in w->dirIndex and returns 1; otherwise returns 0. */
s32 func_800C2634(Wrestler *w, u16 arg1) {
    s16 direction;
    s32 angle;
    u32 flag;

    if (func_800D7B08(arg1) != -1) {
        if (arg1 == 0x900) direction = 0;
        if (arg1 == 0x500) direction = 1;
        if (arg1 == 0x600) direction = 2;
        if (arg1 == 0xA00) direction = 3;
        angle = func_800D3550(func_800D3684(D_800E3C90[direction], w->heading));
        if ((u32)(angle - 0x201) < 0x3FF) {
            direction = (direction + 1) & 3;
        }
    } else {
        if (arg1 == 0x800) direction = 0;
        if (arg1 == 0x100) direction = 1;
        if (arg1 == 0x400) direction = 2;
        if (arg1 == 0x200) direction = 3;
    }
    angle = func_800D3550(func_800D3684(D_800E3C90[direction], w->heading));
    flag = w->hitInfo >> 12;
    if (((flag & 1) & (angle < 0xE3)) || (((flag ^ 1) & 1) & (angle >= 0x71D))) {
        w->dirIndex = direction;
        return 1;
    }
    return 0;
}
