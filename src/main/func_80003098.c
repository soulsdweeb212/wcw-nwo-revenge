#include "common.h"

void initializeTransformNode(void *, s8, f32, f32, f32);

/* Initializes a transform node and clears its 0x28-byte sub-record. */
void func_80004B34(void *arg0, u8 *arg1, s8 arg2, f32 arg3, f32 arg4, f32 arg5) {
    initializeTransformNode(arg0, arg2, arg3, arg4, arg5);
    arg1[0] = 0;
    arg1[1] = 0;
    arg1[2] = 0;
    arg1[3] = 0;
    arg1[4] = 0;
    arg1[5] = 0;
    *(s32 *)(arg1 + 0xC) = 0;
    *(s32 *)(arg1 + 0x10) = 0;
    *(s32 *)(arg1 + 0x14) = 0;
    *(s32 *)(arg1 + 0x18) = 0;
    *(s32 *)(arg1 + 0x1C) = 0;
    *(s32 *)(arg1 + 0x20) = 0;
    *(s32 *)(arg1 + 0x24) = 0;
}

s32 func_80014140(s32, s16, s16, s16, s16, s16);
extern s32 D_800482D4;

/* Requests a sound through the shared sound handle. */
void func_800032A4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    func_80014140(D_800482D4, arg0, arg1, arg2, arg3, arg4);
}

extern s32 D_80147000;
extern s32 D_8017F400;
extern s32 D_801B7800;

/* Clears the three large render/work buffers (0xE100 words each). */
void func_80003098(void) {
    s32 *p;
    u32 i;

    p = &D_801B7800;
    for (i = 0; i <= 0xE0FF; i++) {
        *p++ = 0;
    }
    p = &D_8017F400;
    for (i = 0; i <= 0xE0FF; i++) {
        *p++ = 0;
    }
    p = &D_80147000;
    for (i = 0; i <= 0xE0FF; i++) {
        *p++ = 0;
    }
}
