/* @header
 * n_alSynSetPan  (originally func_80017860)
 * VRAM 0x80017860 | ROM 0x18460 | size 0x84
 * asm: asm/nonmatchings/main/n_alSynSetPan.s
 */
/* SDK: n_audio, libnaudio/src/n_synsetpan.c (same code as the SDK source). */
#include "common.h"

extern s32 *D_80036F54;
s32 *__n_allocParam(void);
s32 n_alEnvmixerParam(s32 *, s32, s32 *);
s32 _n_timeToSamples(s32, s32);

/* Sends command 0xC with the byte payload arg1 to the node referenced by arg0[2]. */
void n_alSynSetPan(s32 *arg0, s32 arg1) {
    s32 *p;
    if (arg0[2] != 0) {
        p = __n_allocParam();
        if (p != 0) {
            s32 g = D_80036F54[7];
            s32 off = *(s32 *)((u8 *)arg0[2] + 0x88);
            *(s16 *)((u8 *)p + 8) = 0xC;
            p[3] = arg1 & 0xFF;
            p[0] = 0;
            p[1] = g + off;
            n_alEnvmixerParam((s32 *)arg0[2], 3, p);
        }
    }
}
