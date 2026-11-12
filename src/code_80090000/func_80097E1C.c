/* @header
 * func_80097E1C
 * VRAM 0x80097E1C | ROM 0x4458C | size 0x244
 * asm: asm/nonmatchings/code_80090000/func_80097E1C.s
 */
#include "common.h"

typedef struct {
    u8 pad0[4];
    u16 w;
    u16 h;
} Nw2Tex97E1C;

#ifdef TARGET_PC
/* PC: the display list at 0x800C95F0 by its own address (port.h's DL_ADDR turns it into the command word; D_C95F0 is
 * its N64 physical address, a link constant). func_800B6F88 hands back the texture's and the palette's addresses
 * through pointers to pointers (its definition takes u8 **), and buildTiledTextureDisplayList takes the texture as a
 * pointer (its PC definition). */
extern u8 D_800C95F0[];
Nw2Tex97E1C *func_800B6F88(s32, u8 **, u8 **);
void buildTiledTextureDisplayList(void **, void *, s32, s32, s32, s32, s32, s32, s32, s32);
#else
extern u8 D_C95F0[];
Nw2Tex97E1C *func_800B6F88(s32, s32 *, s32 *);
void buildTiledTextureDisplayList(void **, s32, s32, s32, s32, s32, s32, s32, s32, s32);
#endif

/* Draws a sprite resource scaled by alpha (arg4), positioned from (x, y); flags 0x40000/0x20000 centre it horizontally/
 * vertically, mode bits 0x400/0x100/0x200 pick centred, right- or bottom-aligned. */
#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx (common.h's Nw2GfxCommand is the N64's 8 bytes); the texture and the palette
 * are addresses, so pointers, and the palette's and the branch target's go into the commands as the whole pointers
 * (port.h's DL_ADDR). */
void func_80097E1C(void **out, s32 id, s32 x, s32 y, s32 alpha, s32 flags, s32 mode) {
    void *p;
    u8 *sp28;
    u8 *sp2C;
    Nw2Tex97E1C *tex;
    s32 w;
    s32 h;

    p = *out;
    tex = func_800B6F88(id, &sp28, &sp2C);
    if (tex != NULL) {
        if (alpha != 0) {
            { Gfx *q = p; p = q + 1; q->w0 = 0xDE000000; q->w1 = DL_ADDR(D_800C95F0); }
            { Gfx *q = p; p = q + 1; q->w0 = 0xFD100000; q->w1 = DL_ADDR(sp2C); }
            { Gfx *q = p; p = q + 1; q->w0 = 0xE8000000; q->w1 = 0; }
            { Gfx *q = p; p = q + 1; q->w0 = 0xF5000100; q->w1 = 0x07000000; }
            { Gfx *q = p; p = q + 1; q->w0 = 0xE6000000; q->w1 = 0; }
            { Gfx *q = p; p = q + 1; q->w0 = 0xF0000000; q->w1 = 0x0703C000; }
            { Gfx *q = p; p = q + 1; q->w0 = 0xE7000000; q->w1 = 0; }
            w = (tex->w * alpha / 256) * 0x1E0 / 0x140;
            h = tex->h * alpha / 256;
            if ((flags & 0x40000) || (mode & 0x400)) {
                x -= w / 2;
            } else if (mode & 0x100) {
                x -= w;
            }
            if ((flags & 0x20000) || (mode & 0x400)) {
                y -= h / 2;
            } else if (mode & 0x200) {
                y -= h;
            }
            buildTiledTextureDisplayList(&p, sp28, 0, x, y, tex->w, tex->h, w, h, tex->w);
            *out = p;
        }
    }
}
#else
void func_80097E1C(void **out, s32 id, s32 x, s32 y, s32 alpha, s32 flags, s32 mode) {
    void *p;
    s32 sp28;
    s32 sp2C;
    Nw2Tex97E1C *tex;
    s32 w;
    s32 h;

    p = *out;
    tex = func_800B6F88(id, &sp28, &sp2C);
    if (tex != NULL) {
        if (alpha != 0) {
            { Nw2GfxCommand *q = p; p = q + 1; q->w0 = 0xDE000000; q->w1 = (u32)D_C95F0; }
            { Nw2GfxCommand *q = p; p = q + 1; q->w0 = 0xFD100000; q->w1 = sp2C - 0x80000000; }
            { Nw2GfxCommand *q = p; p = q + 1; q->w0 = 0xE8000000; q->w1 = 0; }
            { Nw2GfxCommand *q = p; p = q + 1; q->w0 = 0xF5000100; q->w1 = 0x07000000; }
            { Nw2GfxCommand *q = p; p = q + 1; q->w0 = 0xE6000000; q->w1 = 0; }
            { Nw2GfxCommand *q = p; p = q + 1; q->w0 = 0xF0000000; q->w1 = 0x0703C000; }
            { Nw2GfxCommand *q = p; p = q + 1; q->w0 = 0xE7000000; q->w1 = 0; }
            w = (tex->w * alpha / 256) * 0x1E0 / 0x140;
            h = tex->h * alpha / 256;
            if ((flags & 0x40000) || (mode & 0x400)) {
                x -= w / 2;
            } else if (mode & 0x100) {
                x -= w;
            }
            if ((flags & 0x20000) || (mode & 0x400)) {
                y -= h / 2;
            } else if (mode & 0x200) {
                y -= h;
            }
            buildTiledTextureDisplayList(&p, sp28, 0, x, y, tex->w, tex->h, w, h, tex->w);
            *out = p;
        }
    }
}
#endif
