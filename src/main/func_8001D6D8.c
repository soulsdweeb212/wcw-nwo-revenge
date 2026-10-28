#include "common.h"

extern void func_8001F070(void *obj, void *f1, void *f2, s32 n);
extern s32 func_80020090();
extern s32 func_80020190();
extern s32 func_8001F090();
extern s32 func_8001F1D0();
extern s32 pullAudioMixerChildren();
extern s32 func_8001E30C();

/* Initialize a 3-callback node, clearing +0x14 and setting +0x18 = 1. */
void func_8001D6D8(u8 *arg0) {
    func_8001F070(arg0, func_80020090, func_80020190, 3);
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x18) = 1;
}
