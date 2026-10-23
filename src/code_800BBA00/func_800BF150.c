#include "common.h"

s8 func_800D26A0(void *, s32, s8);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);
extern u8 D_800F9D7C[];

/* Returns 1 when the entity arg0 faces within 0x400 of the linked entity
 * referenced by *arg1. */
s32 func_800BF150(void *arg0, s8 *arg1) {
    s32 buf[4];
    s8 idx = func_800D26A0(arg0, 0, *arg1);

    if (idx != -1) {
        func_800D3890((u8 *)arg0 + 0x6C, D_800F9D7C + idx * 0x3B0, buf);
        if (func_800D3550(func_800D3684(*(s32 *)((u8 *)arg0 + 0x58), buf[3])) < 0x400)
            return 1;
    }
    return 0;
}
