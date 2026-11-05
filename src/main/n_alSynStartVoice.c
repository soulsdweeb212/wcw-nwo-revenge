/* @header
 * n_alSynStartVoice  (originally func_80017A30)
 * VRAM 0x80017A30 | ROM 0x18630 | size 0x88
 * asm: asm/nonmatchings/main/n_alSynStartVoice.s
 */
/* SDK: n_audio, libnaudio/src/n_synstartvoice.c (same code as the SDK source). */
#include "common.h"

extern s32 *D_80036F54;

s32 *__n_allocParam(void);
s32 n_alEnvmixerParam(s32 *arg0, s32 arg1, s32 *arg2);
s32 n_alEnvmixerPull(s32 arg0, s32 arg1, s32 arg2);

/* Sends command 14 (with payload arg1 and the object's +0x1A word) to the node
 * referenced by arg0[2]. */
void n_alSynStartVoice(s32 *arg0, s32 arg1) {
    s32 *v0;

    if (arg0[2] != 0) {
        v0 = __n_allocParam();
        if (v0 != 0) {
            v0[1] = D_80036F54[7] + *(s32 *)((u8 *)arg0[2] + 0x88);
            *(s16 *)((u8 *)v0 + 8) = 0xE;
            v0[3] = arg1;
            v0[0] = 0;
            *(u16 *)((u8 *)v0 + 0xA) = *(u16 *)((u8 *)arg0 + 0x1A);
            n_alEnvmixerParam((s32 *)arg0[2], 3, v0);
        }
    }
}
