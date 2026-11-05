/* @header
 * __MusIntSetVolumeAndPan  (originally func_80014DF4)
 * VRAM 0x80014DF4 | ROM 0x159F4 | size 0x168
 * asm: asm/nonmatchings/main/__MusIntSetVolumeAndPan.s
 */
/* SDK: libmus, libmus/src/player.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

void n_alSynSetPan(void *, u8);
void n_alSynSetVol(void *, s16, s32);

extern s32 mus_voices;
extern s32 mus_next_frame_time;
extern u16 mus_master_volume_effects;
extern u16 mus_master_volume_songs;
extern s32 D_80060500;

/* Recomputes audio voice arg1's output volume (s16 +0xC0) and pan (byte +0xDE)
 * from its per-voice mix factors, clamps them, and forwards changed values to
 * the audio mixer (n_alSynSetVol for volume, n_alSynSetPan for pan). */
void __MusIntSetVolumeAndPan(u8 *arg0, s32 arg1) {
    u32 v;
    s32 scale;
    s32 rate;

    v = (u32)(arg0[0xDC] * arg0[0xE4] * arg0[0xDB] * *(s16 *)(arg0 + 0xBE)) >> 13;
    if (v > 0x7FFF) {
        v = 0x7FFF;
    }
    if (*(u16 *)(arg0 + 0xC6) == 0) {
        scale = mus_master_volume_songs;
    } else {
        scale = mus_master_volume_effects;
    }
    v *= scale;
    v >>= 15;
    rate = *(s32 *)(arg0 + 0x18);
    if (rate != -1) {
        v = (u32)(v * rate) / *(u32 *)(arg0 + 0x30);
    }
    if (v != *(u16 *)(arg0 + 0xC0)) {
        *(u16 *)(arg0 + 0xC0) = v;
        n_alSynSetVol((s32 *)(mus_voices + arg1 * 0x1C), v, mus_next_frame_time);
    }
    v = arg0[0xDD];
    v = ((u32)(v * *(s16 *)(arg0 + 0xD0)) >> 7) & 0x7F;
    if (v != arg0[0xDE]) {
        arg0[0xDE] = v;
        if (D_80060500 != 0) {
            v = 0x40;
        }
        n_alSynSetPan((s32 *)(mus_voices + arg1 * 0x1C), v);
    }
}
