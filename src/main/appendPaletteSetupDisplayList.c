/* @header
 * appendPaletteSetupDisplayList  (originally func_8002A970)
 * VRAM 0x8002A970 | ROM 0x2B570 | size 0xB8
 * asm: asm/nonmatchings/main/func_8002A970.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } Cmd;
extern u8 D_80038D80[], D_80038DB0[];

/* Append the standard palette/texture setup commands to the display list pointed
 * to by *arg0: load the palette (0xDE000000) and texture image (0xFD100000), set
 * the tile, load block and set up the 2bpp texture, then update the caller's
 * pointer. */
void appendPaletteSetupDisplayList(Cmd **arg0) {
    Cmd *p = *arg0;
    { Cmd *q = p++; q->w0 = 0xDE000000; q->w1 = (u32)(D_80038D80 - 0x80000000); }
    { Cmd *q = p++; q->w0 = 0xFD100000; q->w1 = (u32)(D_80038DB0 - 0x80000000); }
    { Cmd *q = p++; q->w0 = 0xE8000000; q->w1 = 0; }
    { Cmd *q = p++; q->w0 = 0xF5000100; q->w1 = 0x07000000; }
    { Cmd *q = p++; q->w0 = 0xE6000000; q->w1 = 0; }
    { Cmd *q = p++; q->w0 = 0xF0000000; q->w1 = 0x0703C000; }
    { Cmd *q = p++; q->w0 = 0xE7000000; q->w1 = 0; }
    *arg0 = p;
}
