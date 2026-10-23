#include "common.h"

void func_80004E08(void *, s16, s16);
void buildCiTextureDisplayList(void *, s32);

/* Build the CI-texture node at the given size. */
void func_80004F80(void *arg0, s16 arg1, s16 arg2) {
    func_80004E08(arg0, arg1, arg2);
    buildCiTextureDisplayList(arg0, 0);
}

void initializeTransformNode(void *, s8, s32, f32, f32);

/* Initialize a transform node and clear its descriptor. */
void func_80004B34(void *arg0, u8 *arg1, s8 arg2, s32 arg3, f32 arg4, f32 arg5) {
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

/* Forward five parameters to func_80014140 with the current context D_800482D4. */
void func_800032A4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    func_80014140(D_800482D4, arg0, arg1, arg2, arg3, (s16)arg4);
}

extern s32 D_80147000;
extern s32 D_8017F400;
extern s32 D_801B7800;

/* Clear three 0x38400-word buffers. */
void func_80003098(void) {
    s32 *p;
    s32 i;

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
