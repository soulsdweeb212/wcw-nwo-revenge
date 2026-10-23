#include "common.h"

s32 func_800D35B0(s32, s32);
s32 func_800D4B10(void *);

/* Snapshot the entity's animation byte into +0x42, advance its heading by the +0x368
 * delta, then update its transform. */
void func_800D4AD0(void *arg0) {
    *(u8 *)((u8 *)arg0 + 0x42) = (u8) *(u8 *)((u8 *)arg0 + 0x36F);
    *(s32 *)((u8 *)arg0 + 0x58) = func_800D35B0(*(s32 *)((u8 *)arg0 + 0x58), *(s32 *)((u8 *)arg0 + 0x368));
    func_800D4B10(arg0);
}
