/* @header
 * func_8001D67C
 * VRAM 0x8001D67C | ROM 0x1E27C | size 0x5C
 * asm: asm/nonmatchings/main/func_8001D67C.s
 */
#include "common.h"

extern void func_8001F070(void *obj, void *f1, void *f2, s32 n);
extern s32 func_80020090();
extern s32 func_80020190();
extern s32 func_8001F090();
extern s32 func_8001F1D0();
extern s32 pullAudioMixerChildren();
extern s32 func_8001E30C();

/* Initialize a 7-callback node, storing arg2/arg1 at +0x18/+0x1C. */
void func_8001D67C(u8 *arg0, s32 arg1, s32 arg2) {
    func_8001F070(arg0, func_8001F090, func_8001F1D0, 7);
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x18) = arg2;
    *(s32 *)(arg0 + 0x1C) = arg1;
}
