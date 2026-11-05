/* @header
 * __n_allocParam  (originally func_80017F18)
 * VRAM 0x80017F18 | ROM 0x18B18 | size 0x2C
 * asm: asm/nonmatchings/main/__n_allocParam.s
 */
/* SDK: n_audio, libnaudio/src/n_synthesizer.c (same code as the SDK source). */
#include "common.h"

extern void *n_syn;

/* Pop and return a command packet from the free list at n_syn+0x2C. */
s32 *__n_allocParam(void) {
    s32 *pkt;
    s32 *ret;

    pkt = *(s32 **)((u8 *)n_syn + 0x2C);
    ret = NULL;
    if (pkt != NULL) {
        ret = pkt;
        *(s32 **)((u8 *)n_syn + 0x2C) = (s32 *) *ret;
        *ret = NULL;
    }
    return ret;
}
