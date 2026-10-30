/* @header
 * updateAudioVoiceVolume  (originally func_80014DF4)
 * VRAM 0x80014DF4 | ROM 0x159F4 | size 0x168
 * asm: asm/nonmatchings/main/updateAudioVoiceVolume.s
 */
#include "common.h"

void func_80017860(void *, u8);
void func_80017980(void *, s16, s32);

extern s32 D_800604CC;
extern s32 D_800604E0;
extern u16 D_800604E4;
extern u16 D_800604E6;
extern s32 D_80060500;

/* Recomputes audio voice arg1's output volume (s16 +0xC0) and pan (byte +0xDE)
 * from its per-voice mix factors, clamps them, and forwards changed values to
 * the audio mixer (func_80017980 for volume, func_80017860 for pan). */
void updateAudioVoiceVolume(u8 *arg0, s32 arg1) {
    u32 v;
    s32 scale;
    s32 rate;

    v = (u32)(arg0[0xDC] * arg0[0xE4] * arg0[0xDB] * *(s16 *)(arg0 + 0xBE)) >> 13;
    if (v > 0x7FFF) {
        v = 0x7FFF;
    }
    if (*(u16 *)(arg0 + 0xC6) == 0) {
        scale = D_800604E6;
    } else {
        scale = D_800604E4;
    }
    v *= scale;
    v >>= 15;
    rate = *(s32 *)(arg0 + 0x18);
    if (rate != -1) {
        v = (u32)(v * rate) / *(u32 *)(arg0 + 0x30);
    }
    if (v != *(u16 *)(arg0 + 0xC0)) {
        *(u16 *)(arg0 + 0xC0) = v;
        func_80017980((s32 *)(D_800604CC + arg1 * 0x1C), v, D_800604E0);
    }
    v = arg0[0xDD];
    v = ((u32)(v * *(s16 *)(arg0 + 0xD0)) >> 7) & 0x7F;
    if (v != arg0[0xDE]) {
        arg0[0xDE] = v;
        if (D_80060500 != 0) {
            v = 0x40;
        }
        func_80017860((s32 *)(D_800604CC + arg1 * 0x1C), v);
    }
}
