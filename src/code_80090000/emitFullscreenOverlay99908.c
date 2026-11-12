/* @header
 * emitFullscreenOverlay99908  (originally func_80099908)
 * VRAM 0x80099908 | ROM 0x46078 | size 0x260
 * asm: asm/nonmatchings/code_80090000/emitFullscreenOverlay99908.s
 */
#include "common.h"

/* Emits a full-screen overlay for screen flash/fade effects.
 * Always emits a texture load (0xDE) for the effect texture, then the two
 * render-mode setup words (0xE3) and a combine-mode word (0xFC) choosing the
 * blender. arg1 selects the additive ("burn", high byte colour) versus
 * subtractive ("fade", low byte colour) variant: both take their intensity
 * byte from D_800D5D1C[0x20F] and set a different cycle word
 * (0x442048 / 0x4041C8).
 * The border inset n (D_800D5D1C+0x208) then selects either a
 * plain quad (n == 0) or a tiled quad inset by n on all sides. It finishes
 * by restoring the render mode and binding the D_800C9B5C texture
 * before the 0xDF end word. */
extern void *D_800E9F80;
extern u8 D_800C5AD0[];
extern u8 D_800D5D1C[];
extern u8 D_800C9B5C[];
void func_80096D8C(void **, void *, s32, s32, s32, s32, s32, s32, s32);
void buildTiledTextureDisplayList(void **, void *, s32, s32, s32, s32, s32, s32, s32, s32);

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx, which func_80096D8C and buildTiledTextureDisplayList also write on PC, and
 * the two branch targets go into it as whole pointers (port.h's DL_ADDR). The N64 code reaches them through the
 * addresses of nearby labels: (u32)D_800C5AD0 - 0x7FFFC598 is the physical address of the display list D_800C9538
 * (the asm loads D_C9538), and D_800C9B5C + 0x114 is D_800C9C70; the PC names them. The effect's settings are the
 * labels the asm reads: the border inset D_800D5F24 (D_800D5D1C + 0x208), and the intensity D_800D5F2B
 * (D_800D5D1C + 0x20F), the low byte of the s32 D_800D5F28 on the big-endian N64, which on PC is (u8)D_800D5F28
 * (docs/port.md, "Byte order on PC"). */
extern u8 D_800C9538[];
extern u8 D_800C9C70[];
extern s32 D_800D5F24;
extern s32 D_800D5F28;
void emitFullscreenOverlay99908(Gfx **arg0, s32 arg1) {
    Gfx *p;
    s32 inset;

    p = *arg0;
    { Gfx *q = p++; q->w0 = 0xDE000000; q->w1 = DL_ADDR(D_800C9538); }
    { Gfx *q = p++; q->w0 = 0xE3001201; q->w1 = 0; }
    { Gfx *q = p++; q->w0 = 0xE3001001; q->w1 = 0; }
    { Gfx *q = p++; q->w0 = 0xFC119623; q->w1 = 0xFF2FFFFF; }

    if (arg1) {
        u32 c = (u8)D_800D5F28;
        { Gfx *q = p++; q->w0 = 0xE200001C; q->w1 = 0x442048; }
        { Gfx *q = p++; q->w0 = 0xFA000000; q->w1 = (c << 24) | (c << 16) | (c << 8) | 0xFF; }
    } else {
        u32 c = (u8)D_800D5F28;
        { Gfx *q = p++; q->w0 = 0xE200001C; q->w1 = 0x4041C8; }
        { Gfx *q = p++; q->w0 = 0xFA000000; q->w1 = c | 0xFFFFFF00; }
    }

    inset = D_800D5F24;
    if (inset == 0) {
        { Gfx *q = p++; q->w0 = 0xE3000C00; q->w1 = 0; }
        func_80096D8C((void **)&p, D_800E9F80, 2, 0, 0, 0x1E0, 0xF0, 0x1E0, 0xF0);
    } else {
        { Gfx *q = p++; q->w0 = 0xE3000C00; q->w1 = 0x80000; }
        buildTiledTextureDisplayList((void **)&p, D_800E9F80, 2, inset, inset, 0x1E0, 0xF0, 0x1E0 - inset * 2, 0xF0 - inset * 2, 0x1E0);
    }

    { Gfx *q = p++; q->w0 = 0xE3001201; q->w1 = 0x2000; }
    { Gfx *q = p++; q->w0 = 0xE3001001; q->w1 = 0x8000; }
    { Gfx *q = p++; q->w0 = 0xDE000000; q->w1 = DL_ADDR(D_800C9C70); }
    { Gfx *q = p++; q->w0 = 0xDF000000; q->w1 = 0; }
    *arg0 = p;
}
#else
void emitFullscreenOverlay99908(Nw2GfxCommand **arg0, s32 arg1) {
    Nw2GfxCommand *p;
    s32 inset;

    p = *arg0;
    { Nw2GfxCommand *q = p++; q->w0 = 0xDE000000; q->w1 = (u32)D_800C5AD0 - 0x7FFFC598; }
    { Nw2GfxCommand *q = p++; q->w0 = 0xE3001201; q->w1 = 0; }
    { Nw2GfxCommand *q = p++; q->w0 = 0xE3001001; q->w1 = 0; }
    { Nw2GfxCommand *q = p++; q->w0 = 0xFC119623; q->w1 = 0xFF2FFFFF; }

    if (arg1) {
        s32 c = ((u8 *)D_800D5D1C)[0x20F];
        { Nw2GfxCommand *q = p++; q->w0 = 0xE200001C; q->w1 = 0x442048; }
        { Nw2GfxCommand *q = p++; q->w0 = 0xFA000000; q->w1 = (c << 24) | (c << 16) | (c << 8) | 0xFF; }
    } else {
        s32 c = ((u8 *)D_800D5D1C)[0x20F];
        { Nw2GfxCommand *q = p++; q->w0 = 0xE200001C; q->w1 = 0x4041C8; }
        { Nw2GfxCommand *q = p++; q->w0 = 0xFA000000; q->w1 = c | 0xFFFFFF00; }
    }

    inset = *((s32 *)((u8 *)D_800D5D1C + 0x208));
    if (inset == 0) {
        { Nw2GfxCommand *q = p++; q->w0 = 0xE3000C00; q->w1 = 0; }
        func_80096D8C((void **)&p, D_800E9F80, 2, 0, 0, 0x1E0, 0xF0, 0x1E0, 0xF0);
    } else {
        { Nw2GfxCommand *q = p++; q->w0 = 0xE3000C00; q->w1 = 0x80000; }
        buildTiledTextureDisplayList((void **)&p, D_800E9F80, 2, inset, inset, 0x1E0, 0xF0, 0x1E0 - inset * 2, 0xF0 - inset * 2, 0x1E0);
    }

    { Nw2GfxCommand *q = p++; q->w0 = 0xE3001201; q->w1 = 0x2000; }
    { Nw2GfxCommand *q = p++; q->w0 = 0xE3001001; q->w1 = 0x8000; }
    { Nw2GfxCommand *q = p++; q->w0 = 0xDE000000; q->w1 = (u32)(D_800C9B5C + 0x114); }
    { Nw2GfxCommand *q = p++; q->w0 = 0xDF000000; q->w1 = 0; }
    *arg0 = p;
}
#endif
