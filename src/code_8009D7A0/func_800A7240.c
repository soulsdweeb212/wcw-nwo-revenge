#include "common.h"

s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);

/* Turns the entity's heading (+0x58) toward arg1: if the remaining delta is
 * within arg2 it snaps to arg1 and raises the flags in arg3, returning 1;
 * otherwise it steps the heading by arg2 in the delta's direction and returns 0. */
s32 func_800A7240(void *obj, s32 arg1, s32 arg2, u64 arg3) {
    s32 t;

    t = func_800D3684(arg1, *(s32 *)((u8 *)obj + 0x58));
    if (func_800D3550(t) < arg2) {
        *(s32 *)((u8 *)obj + 0x58) = arg1;
        *(u64 *)((u8 *)obj + 0x20) |= arg3;
        return 1;
    }
    if (t >= 0)
        t = arg2;
    else
        t = -arg2;
    *(s32 *)((u8 *)obj + 0x58) = func_800D35B0(*(s32 *)((u8 *)obj + 0x58), t);
    return 0;
}
