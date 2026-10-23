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

/* Decode the animation frame descriptor: two 16-bit offsets and a base offset. */
s32 func_80016784(S80016784 *arg0, u8 *arg1) {
    s32 a;
    s32 b;
    s32 d;
    s32 c;
    s32 e;
    s32 f;

    a = *arg1++;
    b = *arg1++;
    c = *arg1++;
    d = *arg1++;
    arg0->unkC2 = 1;
    arg0->unk4C = arg0->unkA8 + ((c << 8) + d);
    e = arg1[0];
    f = arg1[1];
    arg0->unkC4 = 1;
    arg0->unk48 = arg0->unkA4 + ((e << 8) + f);
    return arg0->unk9C + ((a << 8) + b);
}
