#include "common.h"

s16 func_800D7B08(s32);
extern s32 D_800E3C90[];

s32 func_800C2634(void *arg0, u16 arg1) {
    s16 direction;
    s32 angle;
    u32 flag;

    if (func_800D7B08(arg1) != -1) {
        if (arg1 == 0x900) direction = 0;
        if (arg1 == 0x500) direction = 1;
        if (arg1 == 0x600) direction = 2;
        if (arg1 == 0xA00) direction = 3;
        angle = func_800D3550(func_800D3684(D_800E3C90[direction], *(s32 *)((u8 *)arg0 + 0x58)));
        if ((u32)(angle - 0x201) < 0x3FF) {
            direction = (direction + 1) & 3;
        }
    } else {
        if (arg1 == 0x800) direction = 0;
        if (arg1 == 0x100) direction = 1;
        if (arg1 == 0x400) direction = 2;
        if (arg1 == 0x200) direction = 3;
    }
    angle = func_800D3550(func_800D3684(D_800E3C90[direction], *(s32 *)((u8 *)arg0 + 0x58)));
    flag = *(u32 *)((u8 *)arg0 + 0x30) >> 12;
    if (((flag & 1) & (angle < 0xE3)) || (((flag ^ 1) & 1) & (angle >= 0x71D))) {
        *(s16 *)((u8 *)arg0 + 0x3E) = direction;
        return 1;
    }
    return 0;
}
