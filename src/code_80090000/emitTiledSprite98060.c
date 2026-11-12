/* @header
 * emitTiledSprite98060  (originally func_80098060)
 * VRAM 0x80098060 | ROM 0x447D0 | size 0x260
 * asm: asm/nonmatchings/code_80090000/emitTiledSprite98060.s
 */
#include "common.h"

/* Emits the display list for a tiled sprite into *arg0.
 * arg1 = sprite resource id, arg2/arg3 = centre X/Y, arg4 = alpha scale
 * (0..255), arg5 = flags (low 16 bits are OR'd with 8 into the resource
 * call; bit 0x8000 letterbox-corrects the width), arg6 = scaling flags
 * (0x10 double size, 0x20 keep computed size).
 * The routine emits the texture-load pair (0xDE) for D_C95F0/D_C95B8, the
 * palette setup, works out the on-screen width/height (clamped to 0x195),
 * scales by alpha unless flag 0x20, calls buildTiledTextureDisplayList with
 * the centred rectangle, then restores texture D_C9620. */
extern u8 D_C95F0[];
extern u8 D_C95B8[];
extern u8 D_C9620[];
void appendPaletteSetupDisplayList(s32 *);
void *func_800B600C(s32, s32);
void buildTiledTextureDisplayList(void **, void *, s32, s32, s32, s32, s32, s32, s32, s32);

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx, which appendPaletteSetupDisplayList and buildTiledTextureDisplayList also
 * write on PC, and the three display lists go into it as whole pointers (port.h's DL_ADDR). D_C95F0, D_C95B8 and
 * D_C9620 are their N64 physical addresses (link constants); the PC names the lists themselves.
 * The sprite is an entry of the resource-name cache (func_800B600C hands back what func_8002A2FC returns for it),
 * whose PC layout is Nw2ResourceEntryHashed in common.h: the picture's address, at +4 on the N64, is the entry's
 * allocation at +8, and the three sizes at +0xC, +0xE and +0x10 are reserved's +4, +6 and +8. Spr98 is that view, and
 * the assert checks that it agrees with the entry. */
extern u8 D_800C95F0[];
extern u8 D_800C95B8[];
extern u8 D_800C9620[];
typedef struct { u8 pad0[8]; void *img; u8 pad10[4]; s16 s0C; s16 s0E; s16 s10; } Spr98;
_Static_assert(offsetof(Spr98, img) == offsetof(Nw2ResourceEntryHashed, allocation) &&
                   offsetof(Spr98, s0C) == offsetof(Nw2ResourceEntryHashed, reserved) + 4 &&
                   offsetof(Spr98, s0E) == offsetof(Nw2ResourceEntryHashed, reserved) + 6 &&
                   offsetof(Spr98, s10) == offsetof(Nw2ResourceEntryHashed, reserved) + 8,
               "Spr98 must follow the PC layout of Nw2ResourceEntryHashed");
void emitTiledSprite98060(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Gfx *g;
    Spr98 *tex;
    s32 w;
    s32 h;
    s32 scw;
    s32 sch;

    g = *arg0;
    tex = func_800B600C(arg1, (arg5 & 0xFFFF) | 8);
    if (tex != NULL) {
        { Gfx *q = g++; q->w0 = 0xDE000000; q->w1 = DL_ADDR(D_800C95F0); }
        { Gfx *q = g++; q->w0 = 0xDE000000; q->w1 = DL_ADDR(D_800C95B8); }
        appendPaletteSetupDisplayList((s32 *)&g);
        if (arg5 & 0x8000)
            w = (tex->s10 * 0x1E0) / 0x140;
        else
            w = tex->s10;
        if (arg6 & 0x10) {
            w *= 2;
            h = tex->s0E * 2;
        } else {
            h = tex->s0E;
        }
        if (w >= 0x196) {
            h = (h * 0x195) / w;
            w = 0x195;
        }
        if (arg6 & 0x20) {
            scw = w;
            sch = h;
        } else {
            scw = (w * arg4) / 255;
            sch = (h * arg4) / 255;
        }
        buildTiledTextureDisplayList((void **)&g, tex->img, 0, arg2 - scw / 2, arg3 - sch / 2,
                      tex->s10, tex->s0E, scw, sch, tex->s0C);
        { Gfx *q = g++; q->w0 = 0xDE000000; q->w1 = DL_ADDR(D_800C9620); }
        *arg0 = g;
    }
}
#else
void emitTiledSprite98060(Nw2GfxCommand **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Nw2GfxCommand *g;
    u8 *tex;
    s32 w;
    s32 h;
    s32 scw;
    s32 sch;

    g = *arg0;
    tex = func_800B600C(arg1, (arg5 & 0xFFFF) | 8);
    if (tex != NULL) {
        { Nw2GfxCommand *q = g++; q->w0 = 0xDE000000; q->w1 = (u32)D_C95F0; }
        { Nw2GfxCommand *q = g++; q->w0 = 0xDE000000; q->w1 = (u32)D_C95B8; }
        appendPaletteSetupDisplayList((s32 *)&g);
        if (arg5 & 0x8000)
            w = (*(s16 *)(tex + 0x10) * 0x1E0) / 0x140;
        else
            w = *(s16 *)(tex + 0x10);
        if (arg6 & 0x10) {
            w *= 2;
            h = *(s16 *)(tex + 0xE) * 2;
        } else {
            h = *(s16 *)(tex + 0xE);
        }
        if (w >= 0x196) {
            h = (h * 0x195) / w;
            w = 0x195;
        }
        if (arg6 & 0x20) {
            scw = w;
            sch = h;
        } else {
            scw = (w * arg4) / 255;
            sch = (h * arg4) / 255;
        }
        buildTiledTextureDisplayList((void **)&g, *(void **)(tex + 4), 0, arg2 - scw / 2, arg3 - sch / 2,
                      *(s16 *)(tex + 0x10), *(s16 *)(tex + 0xE), scw, sch, *(s16 *)(tex + 0xC));
        { Nw2GfxCommand *q = g++; q->w0 = 0xDE000000; q->w1 = (u32)D_C9620; }
        *arg0 = g;
    }
}
#endif
