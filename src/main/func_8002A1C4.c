/* @header
 * func_8002A1C4
 * VRAM 0x8002A1C4 | ROM 0x2ADC4 | size 0x138
 * asm: asm/nonmatchings/main/func_8002A1C4.s
 */
#include "common.h"

typedef struct {
    u8 p0[4];
    u8 *pixels;    /* @0x4: packed 2bpp pixel buffer */
    u8 p8[4];
    s16 width;     /* @0xC: grid width in pixels */
    s16 height;    /* @0xE: grid height in pixels */
} Nw2Grid2A1C4;
#ifdef TARGET_PC
/* PC: o is an entry of the resource-name cache (func_8002A2FC passes it), whose PC layout is Nw2ResourceEntryHashed in
 * common.h. On PC the view's pointer field (pixels) is 8 bytes and starts at a multiple of 8, so it lies at +8, the
 * entry's allocation, and width and height fall at reserved's +4 and +6 (+0x14 and +0x16), not at the N64 offsets the
 * comments above give; there func_80028F3C writes the row width and the row count. The view needs no PC version of
 * its own; the assert checks that it still agrees with the entry. */
_Static_assert(offsetof(Nw2Grid2A1C4, pixels) == offsetof(Nw2ResourceEntryHashed, allocation) &&
                   offsetof(Nw2Grid2A1C4, width) == offsetof(Nw2ResourceEntryHashed, reserved) + 4 &&
                   offsetof(Nw2Grid2A1C4, height) == offsetof(Nw2ResourceEntryHashed, reserved) + 6,
               "Nw2Grid2A1C4 must follow the PC layout of Nw2ResourceEntryHashed");
#endif

s32 countNibblePixelNeighbors(void *, s32, s32, s32, s32);

/* Scan a packed 2bpp grid; for each pixel, if its four neighbours set any bits
 * in a nibble (high = 0x10, low = 0x1) while the pixel's same nibble is empty,
 * set the corresponding outline bit. */
void func_8002A1C4(Nw2Grid2A1C4 *o) {
    s32 x, y;
    u8 c;
    s32 neighbors;
    for (y = 0; y < o->height; y++) {
        for (x = 0; x < o->width / 2; x++) {
            c = o->pixels[x + y * o->width / 2];
            neighbors = countNibblePixelNeighbors(o, x, y, 2, c);
            if ((neighbors & 0xF0) && !(c & 0xF0)) {
                c |= 0x10;
            }
            if ((neighbors & 0xF) && !(c & 0xF)) {
                c |= 1;
            }
            o->pixels[x + y * o->width / 2] = c;
        }
    }
}
