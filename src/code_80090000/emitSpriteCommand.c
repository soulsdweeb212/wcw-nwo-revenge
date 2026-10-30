/* @header
 * emitSpriteCommand  (originally func_800985CC)
 * VRAM 0x800985CC | ROM 0x44D3C | size 0x238
 * asm: asm/nonmatchings/code_80090000/func_800985CC.s
 */
#include "common.h"

void emitTiledSprite98060(s32 *, s32, s32, s32, s32, s32, s32);
void func_800982C0(s32 *, s32, s32, s32, s32, s32, s32);
void *func_800B600C(s32, s32);
void appendPaletteSetupDisplayList(s32 *);
void func_80096D8C(s32 *, s32, s32, s32, s32, s32, s32, s32, s32);

/* Tiled-sprite command emitter. Dispatches on bits of `flags` to one of the
 * specialised tile emitters; otherwise looks up the sprite for `spriteId`,
 * appends its palette setup, applies the sub-rectangle adjustments derived
 * from `size`/`flags`/`flags2`, and appends the sprite draw command. The
 * two-word command packet at sp28/sp30 is copied back into *out. */
void emitSpriteCommand(s32 *out, s32 spriteId, s32 x, s32 y, s32 size, s32 flags, s32 flags2) {
    s32 sp28[2];
    s32 sp30;
    s32 v;
    s32 adjX;
    s32 adjY;
    s32 f;
    void *sprite;
    s32 *packet;

    v = *out;
    sp28[0] = v;
    if (flags & 0x10000) {
        emitTiledSprite98060(sp28, spriteId, x, y, 0x140 - size / 4, flags, flags2);
    } else if (flags & 0x100000) {
        emitTiledSprite98060(sp28, spriteId, x, y, 0x300 - size * 2, flags, flags2);
    } else if (flags & 0x80000) {
        func_800982C0(sp28, spriteId, x, y, size, flags, flags2);
    } else {
        adjX = x;
        adjY = y;
        f = flags;
        packet = &sp28[0];
        sp30 = v;
        if (flags2 & 0x10)
            f |= 0x8000;
        sprite = func_800B600C(spriteId, (f & 0xFFFF) | 8);
        if (sprite != NULL) {
            appendPaletteSetupDisplayList(&sp30);
            if ((f & 0x40000) || (flags2 & 0x400))
                adjX -= (s16)*(u16 *)((u8 *)sprite + 0x10) / 2;
            if ((f & 0x20000) || (flags2 & 0x400))
                adjY -= (s16)*(u16 *)((u8 *)sprite + 0xE) / 2;
            if (flags2 & 0x100)
                adjX -= *(s16 *)((u8 *)sprite + 0x10);
            if (flags2 & 0x200)
                adjY -= *(s16 *)((u8 *)sprite + 0xE);
            func_80096D8C(&sp30, *(s32 *)((u8 *)sprite + 4), 0, adjX, adjY,
                          *(s16 *)((u8 *)sprite + 0xC), *(s16 *)((u8 *)sprite + 0xE),
                          *(s16 *)((u8 *)sprite + 0xC),
                          (*(s16 *)((u8 *)sprite + 0xE) * (0x200 - size)) / 255);
            *packet = sp30;
        }
    }
    *out = sp28[0];
}
