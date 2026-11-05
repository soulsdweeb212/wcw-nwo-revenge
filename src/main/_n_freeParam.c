/* @header
 * _n_freeParam  (originally func_80017F44)
 * VRAM 0x80017F44 | ROM 0x18B44 | size 0x18
 * asm: asm/nonmatchings/main/_n_freeParam.s
 */
/* SDK: n_audio, libnaudio/src/n_synthesizer.c (same code as the SDK source). */
#include "common.h"

extern s32 *n_syn;

s32 *__n_allocParam(void);
s32 n_alEnvmixerParam(s32 *arg0, s32 arg1, s32 *arg2);
s32 n_alEnvmixerPull(s32 arg0, s32 arg1, s32 arg2);

void _n_freeParam(s32 *arg0) {
    s32 *v1 = n_syn;
    *arg0 = *(s32 *)((u8 *)v1 + 0x2C);
    *(s32 *)((u8 *)v1 + 0x2C) = (s32)arg0;
}
