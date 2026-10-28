#include "common.h"

void func_800015AC(void *, s8);

/* Initializes the object and its sub-record from descriptor arg3, copying the
 * packed descriptor bytes into the sub-record's size/offset fields. */
void func_80007874(u8 *arg0, s32 arg1, s32 arg2, s16 arg3) {
    u8 *t = (u8 *)(arg3 * 0x2C + arg1);
    s32 *p;
    s32 v;

    arg0[0x1A] = t[6];
    *(s32 *)(arg0 + 0xC) = *(s32 *)(t + 0xC);
    func_800015AC(arg0, t[2]);
    p = *(s32 **)(arg0 + 0x14);
    p[0] = 1;
    p[0xC] = 0;
    p[0xD] = 0;
    *(s16 *)((u8 *)p + 0x2C) = (s8)t[2];
    *(s16 *)((u8 *)p + 0x2E) = (s8)t[3];
    v = *(s32 *)(t + 0xC);
    *(s32 *)((u8 *)p + 0x34) = arg2;
    *(s32 *)((u8 *)p + 0x30) = v;
}
