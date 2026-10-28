#include "common.h"

/* Audio-mixer callback: on message 2, append arg2 to the object's argument array. */
s32 func_8001E30C(u8 *arg0, s32 arg1, s32 arg2) {
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
