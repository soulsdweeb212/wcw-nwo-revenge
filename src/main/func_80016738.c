#include "common.h"

typedef struct {
    u8 pad0[0x48];
    s32 unk48;
    s32 unk4C;
    u8 pad50[0x9C - 0x50];
    s32 unk9C;
    u8 padA0[0xA4 - 0xA0];
    s32 unkA4;
    s32 unkA8;
    u8 padAC[0xC2 - 0xAC];
    s16 unkC2;
    s16 unkC4;
} S80016784;

/* Resolve arg0's current keyframe pointer from the animation table indexed by the
 * next byte; advances arg1 when a frame is available. */
u8 *func_80016738(u8 *arg0, u8 *arg1) {
    u8 *temp_v1;
    s32 temp_a2;
    s32 temp_v0;

    temp_v1 = *(u8 **)(arg0 + 0x94);
    temp_a2 = *(s32 *)(temp_v1 + 0x14);
    temp_v0 = *(s32 *)(temp_v1 + 0x10);
    if (temp_a2 != temp_v0) {
        *(u32 *)(arg0 + 0xA0) = (u32)(temp_v1 + *(s32 *)(temp_a2 + *arg1 * 4));
        arg1++;
    } else {
        *(u32 *)(arg0 + 0xA0) = 0;
    }
    return arg1;
}
