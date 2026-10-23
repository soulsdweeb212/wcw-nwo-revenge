#include "common.h"

/* Emit a textured-rectangle display list for a 81x21 HUD tile.
 * Clamps the rectangle to the 480x240 screen, loads the texture at
 * D_800E9F80+offset, sets up a two-triangle (RDP) fill with the tile
 * dimensions and the given colour triple (c, c+1, c+2 scaled), and
 * advances *arg0 past the 8 generated commands. */
extern u16 *D_800E9F80;
void func_80091718(Nw2GfxCommand **arg0, s32 x, s32 y, s32 c, s32 offset) {
    Nw2GfxCommand *cmd = *arg0;
    s32 left, top, right, bottom;
    left = x - 1; left = left & (~left >> 31);
    top = y - 1; top = top & (~top >> 31);
    right = x + 81; if (right > 480) right = 480;
    bottom = y + 21; if (bottom > 240) bottom = 240;
    { Nw2GfxCommand *cur = cmd++; cur->w0 = 0xFD1001DF; cur->w1 = (u32)(D_800E9F80 + offset) - 0x80000000; }
    { Nw2GfxCommand *cur = cmd++; cur->w0 = 0xF5100000 | (((((right - left) * 2 + 9) >> 3) & 0x1FF) << 9); cur->w1 = 0x07080200; }
    { Nw2GfxCommand *cur = cmd++; cur->w0 = 0xE6000000; cur->w1 = 0; }
    { Nw2GfxCommand *cur = cmd++; cur->w0 = 0xF4000000 | (((left * 4) & 0xFFF) << 12) | ((top * 4) & 0xFFF); cur->w1 = 0x07000000 | (((right * 4) & 0xFFF) << 12) | ((bottom * 4) & 0xFFF); }
    { Nw2GfxCommand *cur = cmd++; cur->w0 = 0xE7000000; cur->w1 = 0; }
    { Nw2GfxCommand *cur = cmd++; cur->w0 = 0xF5100000 | (((((right - left) * 2 + 9) >> 3) & 0x1FF) << 9); cur->w1 = 0x00080200; }
    { Nw2GfxCommand *cur = cmd++; cur->w0 = 0xF2000000 | (((left * 4) & 0xFFF) << 12) | ((top * 4) & 0xFFF); cur->w1 = (((right * 4) & 0xFFF) << 12) | ((bottom * 4) & 0xFFF); }
    { Nw2GfxCommand *cur = cmd++; cur->w0 = ((((c + 7) * 2) & 255) << 16) | (((c + 8) << 9) & 0xFE00) | (((c + 1) * 2) & 255) | 0x07000000; cur->w1 = ((((c + 7) * 2) & 255) << 16) | ((((c + 1) * 2) & 255) << 8) | ((c * 2) & 255); }
    *arg0 = cmd;
}
