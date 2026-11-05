/* @header
 * __allocParam  (originally func_800207BC)
 * VRAM 0x800207BC | ROM 0x213BC | size 0x2C
 * asm: asm/nonmatchings/main/__allocParam.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/synthesizer.c (same code as the SDK source). */
#include "common.h"

/* identical to __n_allocParam (matched), with its names changed by decompdecomp */
extern void *D_80037510;

/* Pop and return a command packet from the free list at D_80037510+0x2C. */
s32 *__allocParam(void) {
    s32 *pkt;
    s32 *ret;

    pkt = *(s32 **)((u8 *)D_80037510 + 0x2C);
    ret = NULL;
    if (pkt != NULL) {
        ret = pkt;
        *(s32 **)((u8 *)D_80037510 + 0x2C) = (s32 *) *ret;
        *ret = NULL;
    }
    return ret;
}
