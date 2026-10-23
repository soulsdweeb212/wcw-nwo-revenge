#include "common.h"

/* Audio callback: on message 2, append arg2 to the object's argument array. */
s32 func_8001F1D0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 idx;
    s32 *arr = *(s32 **)(arg0 + 0x1C);

    if (arg1 == 2) {
        idx = *(s32 *)(arg0 + 0x14);
        *(s32 *)(arg0 + 0x14) = idx + 1;
        arr[idx] = arg2;
    }
    return 0;
}

extern void func_8001F070(void *f1, void *f2, s32 n);
extern s32 func_80020090();
extern s32 func_80020190();
extern s32 func_8001F090();
extern s32 func_8001F1D0();
extern s32 pullAudioMixerChildren();

/* Initialize a 3-callback node, clearing +0x14 and setting +0x18 = 1. */
void func_8001D6D8(u8 *arg0) {
    func_8001F070(func_80020090, func_80020190, 3);
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x18) = 1;
}

/* Initialize a 7-callback node, storing arg2/arg1 at +0x18/+0x1C. */
void func_8001D67C(u8 *arg0, s32 arg1, s32 arg2) {
    func_8001F070(func_8001F090, func_8001F1D0, 7);
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x18) = arg2;
    *(s32 *)(arg0 + 0x1C) = arg1;
}

/* Initialize a 6-callback audio-mixer node, storing arg2/arg1 at +0x18/+0x1C. */
void func_8001D620(u8 *arg0, s32 arg1, s32 arg2) {
    func_8001F070(pullAudioMixerChildren, func_8001F1D0, 6);
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x18) = arg2;
    *(s32 *)(arg0 + 0x1C) = arg1;
}
