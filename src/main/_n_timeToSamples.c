/* @header
 * _n_timeToSamples  (originally func_80018044)
 * VRAM 0x80018044 | ROM 0x18C44 | size 0x54
 * asm: asm/nonmatchings/main/_n_timeToSamples.s
 */
/* SDK: n_audio, libnaudio/src/n_synthesizer.c (same code as the SDK source). */
#include "common.h"

extern void *n_syn;
extern f64 D_8003B420;
extern f64 D_8003B428;

/* Scale arg0 by n_syn's +0x40 field, convert to fixed point, and round down to
 * a multiple of 16. */
s32 _n_timeToSamples(s32 arg0) {
    return (s32) (f32) (((f64) ((f32) arg0 * (f32) *(s32 *)((s8 *)n_syn + 0x40)) / D_8003B420) + D_8003B428) & ~0xF;
}
