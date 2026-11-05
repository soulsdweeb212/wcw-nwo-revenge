/* @header
 * __freeParam  (originally func_800207E8)
 * VRAM 0x800207E8 | ROM 0x213E8 | size 0x18
 * asm: asm/nonmatchings/main/__freeParam.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/synthesizer.c (same code as the SDK source). */
#include "common.h"

/* identical to _n_freeParam (matched), with its names changed by decompdecomp */
extern s32 *D_80037510;

s32 *__n_allocParam(void);
s32 n_alEnvmixerParam(s32 *arg0, s32 arg1, s32 *arg2);
s32 n_alEnvmixerPull(s32 arg0, s32 arg1, s32 arg2);

void __freeParam(s32 *arg0) {
    s32 *v1 = D_80037510;
    *arg0 = *(s32 *)((u8 *)v1 + 0x2C);
    *(s32 *)((u8 *)v1 + 0x2C) = (s32)arg0;
}
