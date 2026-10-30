/* @header
 * emitFullscreenOverlay99908  (originally func_80099908)
 * VRAM 0x80099908 | ROM 0x46078 | size 0x260
 * asm: asm/nonmatchings/code_80090000/func_80099908.s
 */
#include "common.h"

/* Emits a full-screen overlay for screen flash/fade effects.
 * Always emits a texture load (0xDE) for the effect texture, then the two
 * render-mode setup words (0xE3) and a combine-mode word (0xFC) choosing the
 * blender. arg1 selects the additive ("burn", high byte colour) versus
 * subtractive ("fade", low byte colour) variant: both take their intensity
 * byte from stepRecordedFramePlayback[0x20F] and set a different cycle word
 * (0x442048 / 0x4041C8).
 * The border inset n (stepRecordedFramePlayback+0x208) then selects either a
 * plain quad (n == 0) or a tiled quad inset by n on all sides. It finishes
 * by restoring the render mode and binding the updateRingLeapAction texture
 * before the 0xDF end word. */
extern void *D_800E9F80;
extern u8 sceneNodeCallback5AD0[];
extern u8 stepRecordedFramePlayback[];
extern u8 updateRingLeapAction[];
void func_80096D8C(void **, void *, s32, s32, s32, s32, s32, s32, s32);
void buildTiledTextureDisplayList(void **, void *, s32, s32, s32, s32, s32, s32, s32, s32);

void emitFullscreenOverlay99908(Nw2GfxCommand **arg0, s32 arg1) {
    Nw2GfxCommand *p;
    s32 inset;

    p = *arg0;
    { Nw2GfxCommand *q = p++; q->w0 = 0xDE000000; q->w1 = (u32)sceneNodeCallback5AD0 - 0x7FFFC598; }
    { Nw2GfxCommand *q = p++; q->w0 = 0xE3001201; q->w1 = 0; }
    { Nw2GfxCommand *q = p++; q->w0 = 0xE3001001; q->w1 = 0; }
    { Nw2GfxCommand *q = p++; q->w0 = 0xFC119623; q->w1 = 0xFF2FFFFF; }

    if (arg1) {
        s32 c = ((u8 *)stepRecordedFramePlayback)[0x20F];
        { Nw2GfxCommand *q = p++; q->w0 = 0xE200001C; q->w1 = 0x442048; }
        { Nw2GfxCommand *q = p++; q->w0 = 0xFA000000; q->w1 = (c << 24) | (c << 16) | (c << 8) | 0xFF; }
    } else {
        s32 c = ((u8 *)stepRecordedFramePlayback)[0x20F];
        { Nw2GfxCommand *q = p++; q->w0 = 0xE200001C; q->w1 = 0x4041C8; }
        { Nw2GfxCommand *q = p++; q->w0 = 0xFA000000; q->w1 = c | 0xFFFFFF00; }
    }

    inset = *((s32 *)((u8 *)stepRecordedFramePlayback + 0x208));
    if (inset == 0) {
        { Nw2GfxCommand *q = p++; q->w0 = 0xE3000C00; q->w1 = 0; }
        func_80096D8C((void **)&p, D_800E9F80, 2, 0, 0, 0x1E0, 0xF0, 0x1E0, 0xF0);
    } else {
        { Nw2GfxCommand *q = p++; q->w0 = 0xE3000C00; q->w1 = 0x80000; }
        buildTiledTextureDisplayList((void **)&p, D_800E9F80, 2, inset, inset, 0x1E0, 0xF0, 0x1E0 - inset * 2, 0xF0 - inset * 2, 0x1E0);
    }

    { Nw2GfxCommand *q = p++; q->w0 = 0xE3001201; q->w1 = 0x2000; }
    { Nw2GfxCommand *q = p++; q->w0 = 0xE3001001; q->w1 = 0x8000; }
    { Nw2GfxCommand *q = p++; q->w0 = 0xDE000000; q->w1 = (u32)(updateRingLeapAction + 0x114); }
    { Nw2GfxCommand *q = p++; q->w0 = 0xDF000000; q->w1 = 0; }
    *arg0 = p;
}
