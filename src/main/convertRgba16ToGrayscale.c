/* @header
 * convertRgba16ToGrayscale  (originally func_80004C90)
 * VRAM 0x80004C90 | ROM 0x5890 | size 0x178
 * asm: asm/nonmatchings/main/convertRgba16ToGrayscale.s
 */
#include "common.h"

/*
 * Convert `pixelCount` RGBA16 texels in place to grayscale, keeping the
 * 1-bit alpha and replicating the weighted luminance into R, G and B.
 * D_8003B0F0 / D_8003B100 / D_8003B108 are the per-channel (G, B, sum)
 * f64 weighting factors.
 */
extern const f64 D_8003B0F0, D_8003B100, D_8003B108;
void convertRgba16ToGrayscale(u16 *pixels, u16 pixelCount) {
    u32 i;
    u16 pixel, r, g, b, a, gray;
    for (i = 0; i < pixelCount; i++, pixels++) {
        pixel = *pixels;
        r = pixel >> 11;
        g = (pixel >> 6) & 31;
        b = (pixel >> 1) & 31;
        a = pixel & 1;
        g = (u32)(g * D_8003B0F0);
        b = (u32)(b * D_8003B100);
        gray = (u32)((r + g + b) * D_8003B108);
        *pixels = a | ((gray << 11) | (gray << 6) | (gray << 1));
    }
}
