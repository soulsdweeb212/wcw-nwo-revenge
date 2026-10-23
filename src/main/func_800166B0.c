#include "common.h"

/* Decode a one-byte envelope step into +0xF2/+0xF3. */
u8 *func_80016700(u8 *arg0, u8 *arg1) {
    u8 v = *arg1;
    arg0[0xF2] = 0;
    arg0[0xF3] = v;
    return arg1 + 1;
}

/* Decode a one-byte envelope step into +0xDD/+0xDE. */
u8 *func_80016714(u8 *arg0, u8 *arg1) {
    u8 v = *arg1;
    arg0[0xDE] = 0xFF;
    arg0[0xDD] = v >> 1;
    return arg1 + 1;
}

/* Decode a three-byte loop envelope into +0xF8/+0xEE/+0xEF. */
u8 *func_800166B0(u8 *arg0, u8 *arg1) {
    arg0[0xF8] = *arg1++;
    arg0[0xEE] = *arg1++;
    arg0[0xEF] = *arg1;
    return arg1 + 1;
}

/* Push the current sequence-loop state onto the voice's loop stack. */
u8 *pushAudioSequenceLoopState(u8 *arg0, u8 *arg1) {
    u8 idx = arg0[0xFB];
    u8 *a0;
    u8 *v0;
    f32 f;
    f32 c;
    arg1++;
    a0 = arg0 + idx;
    a0[0x140] = arg1[-1];
    v0 = arg0 + idx * 4;
    *(u8 **)(v0 + 0x100) = arg1;
    *(s32 *)(v0 + 0x110) = *(s32 *)(arg0 + 0x4C);
    *(s32 *)(v0 + 0x120) = *(s32 *)(arg0 + 0x48);
    a0[0x144] = arg0[0xDC];
    f = *(f32 *)(arg0 + 0x90);
    c = 2147483648.0f;
    if (f >= c) {
        a0[0x148] = (s8)((s32)(f - c) | 0x80000000);
    } else {
        a0[0x148] = (s8)(s32)f;
    }
    v0 = arg0 + idx * 2;
    *(u16 *)(v0 + 0x130) = *(u16 *)(arg0 + 0xC2);
    *(u16 *)(v0 + 0x138) = *(u16 *)(arg0 + 0xC4);
    arg0[0xFB] = arg0[0xFB] + 1;
    return arg1;
}
