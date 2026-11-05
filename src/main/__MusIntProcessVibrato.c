/* @header
 * __MusIntProcessVibrato  (originally func_800155CC)
 * VRAM 0x800155CC | ROM 0x161CC | size 0x5C
 * asm: asm/nonmatchings/main/__MusIntProcessVibrato.s
 */
/* SDK: libmus, libmus/src/player.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

f32 sinf(f32);

/* Interpolates the audio voice's envelope level: when the elapsed counter
 * (+0xCA) exceeds the start (+0xD6), computes sin((elapsed-start) * step(+0xFC))
 * * level(+0x34) into +0x88 and returns it. */
f32 __MusIntProcessVibrato(void *arg0) {
    s32 temp_v1;

    temp_v1 = *(u16 *)((u8 *)arg0 + 0xCA) - *(u8 *)((u8 *)arg0 + 0xD6);
    if (temp_v1 > 0) {
        *(f32 *)((u8 *)arg0 + 0x88) = (f32) (sinf((f32) temp_v1 * *(f32 *)((u8 *)arg0 + 0xFC)) * *(f32 *)((u8 *)arg0 + 0x34));
    }
    return *(f32 *)((u8 *)arg0 + 0x88);
}
