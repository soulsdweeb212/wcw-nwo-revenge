#include "common.h"

extern s32 gRandSeed;
extern s32 D_800EB634;
extern u16 D_800EB638[];

s32 func_8001C580(void);
void func_800D427C(void *, s32);

s32 func_800D4204(void) {
    s32 x;
    s16 y;
    do {
        x = gRandSeed * 0x5D588B65 + D_800EB634;
        gRandSeed = x;
        y = (s16)(((u64)(u32)(x & 0xFFFFF) * 0x10624DD3u) >> 38);
    } while (y >= 1000);
    return y;
}

s32 func_800D4148(void) {
    s32 idx = func_8001C580() & 0x1F;
    u16 *p = &D_800EB638[idx];
    u16 old = *p;
    *p = func_800D4204();
    return (s16)old;
}

s32 func_800D4198(s16 arg0) {
    s32 idx = func_8001C580() & 0x1F;
    u16 *p = &D_800EB638[idx];
    u16 old = *p;
    *p = func_800D4204();
    return arg0 >= (s16)old;
}

/* Reset the entity's s16 +8 state to -1, then invoke func_800D427C. */
void func_800D43B4(void *entity, s16 action) {
    *(s16 *)((u8 *)entity + 8) = -1;
    func_800D427C(entity, action);
}
