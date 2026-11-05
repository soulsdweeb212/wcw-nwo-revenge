/* @header
 * n_alSynSetPitch  (originally func_800178F0)
 * VRAM 0x800178F0 | ROM 0x184F0 | size 0x84
 * asm: asm/nonmatchings/main/n_alSynSetPitch.s
 */
/* SDK: n_audio, libnaudio/src/n_synsetpitch.c (same code as the SDK source). */
#include "common.h"

extern s32 *n_syn;
s32 *__n_allocParam(void);
s32 n_alEnvmixerParam(s32 *, s32, s32 *);
s32 _n_timeToSamples(s32, s32);

/* Sends command 7 with the float payload arg1 to the node referenced by arg0[2]. */
void n_alSynSetPitch(s32 *arg0, f32 arg1) {
    s32 *p;
    if (arg0[2] != 0) {
        p = __n_allocParam();
        if (p != 0) {
            s32 g = n_syn[7];
            s32 off = *(s32 *)((u8 *)arg0[2] + 0x88);
            *(s16 *)((u8 *)p + 8) = 7;
            *(f32 *)((u8 *)p + 0xC) = arg1;
            p[0] = 0;
            p[1] = g + off;
            n_alEnvmixerParam((s32 *)arg0[2], 3, p);
        }
    }
}
