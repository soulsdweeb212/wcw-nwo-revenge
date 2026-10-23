#include "common.h"

/* Mirror a texture horizontally in place: allocate a scratch row, reverse each
 * row through it (swapping nibbles per byte for 4bpp, plain bytes for 8bpp),
 * then free the scratch. The 1<<width/height fields give the pixel dimensions. */
void *allocateHeap(u32);
void releaseHeapBlock(void *);
typedef struct { u8 pad[2]; u8 kind; u8 pad3[3]; u8 width, height; } Nw2TextureHeader6E7C;

void func_80006E7C(Nw2TextureHeader6E7C *texture) {
    u32 width, height, x, y;
    u8 *rowBuf, *data;
    width = 1 << texture->width;
    height = 1 << texture->height;
    data = (u8 *)(texture + 1);
    rowBuf = allocateHeap(width);
    if (texture->kind != 1) {
        for (y = 0; y < height; y++) {
            for (x = 0; x < width / 2;) {
                u32 halfW = width / 2;
                u32 colNext = x + 1;
                u8 *dst = rowBuf + (halfW - colNext);
                u8 b = data[x + y * (width / 2)];
                x = colNext;
                *dst = (b >> 4) | (b << 4);
            }
            for (x = 0; x < width / 2; x++)
                data[x + y * (width / 2)] = rowBuf[x];
        }
    } else {
        for (y = 0; y < height; y++) {
            for (x = 0; x < width;) {
                u32 colNext = x + 1;
                u8 *dst = rowBuf + (width - colNext);
                u8 b = data[x + y * width];
                x = colNext;
                *dst = b;
            }
            for (x = 0; x < width; x++)
                data[x + y * width] = rowBuf[x];
        }
    }
    releaseHeapBlock(rowBuf);
}
