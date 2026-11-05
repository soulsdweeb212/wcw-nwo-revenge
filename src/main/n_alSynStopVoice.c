/* @header
 * n_alSynStopVoice  (originally func_80017AC0)
 * VRAM 0x80017AC0 | ROM 0x186C0 | size 0x74
 * asm: asm/nonmatchings/main/n_alSynStopVoice.s
 */
/* SDK: n_audio, libnaudio/src/n_synstopvoice.c (same code as the SDK source). */
#include "common.h"

extern s32 *n_syn;

s32 *__n_allocParam(void);
s32 n_alEnvmixerParam(s32 *arg0, s32 arg1, s32 *arg2);
s32 n_alEnvmixerPull(s32 arg0, s32 arg1, s32 arg2);

/* Sends command 15 (with payload arg1) to the node referenced by arg0[2]. */
void n_alSynStopVoice(s32 *arg0) {
    s32 *v0;

    if (arg0[2] != 0) {
        v0 = __n_allocParam();
        if (v0 != 0) {
            v0[1] = n_syn[7] + *(s32 *)((u8 *)arg0[2] + 0x88);
            *(s16 *)((u8 *)v0 + 8) = 0xF;
            v0[0] = 0;
            n_alEnvmixerParam((s32 *)arg0[2], 3, v0);
        }
    }
}
