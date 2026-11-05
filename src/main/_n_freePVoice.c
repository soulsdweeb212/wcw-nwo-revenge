/* @header
 * _n_freePVoice  (originally func_80017FBC)
 * VRAM 0x80017FBC | ROM 0x18BBC | size 0x38
 * asm: asm/nonmatchings/main/_n_freePVoice.s
 */
/* SDK: n_audio, libnaudio/src/n_synthesizer.c (same code as the SDK source). */
#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK alLink(s32, s32);
M2C_UNK alUnlink(void);
extern s32 D_80036F54;

/* Moves the arg0 node to the audio list head at D_80036F54+0x14. */
void _n_freePVoice(s32 arg0) {
    alUnlink();
    alLink(arg0, D_80036F54 + 0x14);
}
