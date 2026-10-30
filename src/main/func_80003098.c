/* @header
 * func_80003098
 * VRAM 0x80003098 | ROM 0x3C98 | size 0x74
 * asm: asm/nonmatchings/main/func_80003098.s
 */
#include "common.h"

void initializeTransformNode(void *, s8, f32, f32, f32);

s32 func_80014140(s32, s16, s16, s16, s16, s16);
extern s32 D_800482D4;

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
