#include "common.h"

f32 sinf(f32);

/* Interpolates the audio voice's envelope level: when the elapsed counter
 * (+0xCA) exceeds the start (+0xD6), computes sin((elapsed-start) * step(+0xFC))
 * * level(+0x34) into +0x88 and returns it. */
f32 func_800155CC(void *arg0) {
    s32 temp_v1;

    temp_v1 = *(u16 *)((u8 *)arg0 + 0xCA) - *(u8 *)((u8 *)arg0 + 0xD6);
    if (temp_v1 > 0) {
        *(f32 *)((u8 *)arg0 + 0x88) = (f32) (sinf((f32) temp_v1 * *(f32 *)((u8 *)arg0 + 0xFC)) * *(f32 *)((u8 *)arg0 + 0x34));
    }
    return *(f32 *)((u8 *)arg0 + 0x88);
}
