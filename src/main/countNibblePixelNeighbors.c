/* @header
 * countNibblePixelNeighbors  (originally func_80029868)
 * VRAM 0x80029868 | ROM 0x2A468 | size 0x1BC
 * asm: asm/nonmatchings/main/func_80029868.s
 */
#include "common.h"

/* Count the same-value neighbours of the pixel at (x,y) in a packed nibble
 * grid (2 pixels per byte, row pitch width/2). The upper nibble and lower
 * nibble are treated separately: when the pixel's high nibble is 0 it counts
 * equal-or-higher high-nibble neighbours above/below/left and the pixel
 * itself; when its low nibble is 0 it counts equal-or-higher low-nibble
 * neighbours above/below plus the high-nibble comparisons for the pixel and
 * right neighbour. `level` is scaled by 16 for the high-nibble comparisons. */
s32 countNibblePixelNeighbors(Nw2NibbleGrid *g, s32 x, s32 y, s32 level, u8 pixel) {
  u8 up, down, left, right, result;
  s32 first, high;
  if (y) up = g->buffer[x + (y - 1) * g->width / 2]; else up = 0;
  if (y < g->height - 1) down = g->buffer[x + (y + 1) * g->width / 2]; else down = 0;
  left = 0;
  if (x) left = g->buffer[y * g->width / 2 + x - 1];
  right = 0;
  if (x < g->width / 2 - 1) { right = g->buffer[y * g->width / 2 + x + 1]; high = level * 16; } else high = level * 16;
  result = 0;
  if (!(pixel & 0xF0)) {
    first = ((u32)(up & 0xF0) >= (u8)high) * 16;
    result = first;
    if ((u32)(down & 0xF0) >= (u8)high) result = first + 16;
    if ((u32)(left & 15) >= (u8)level) result += 16;
    if ((u32)(pixel & 15) >= (u8)level) result += 16;
  }
  if (!(pixel & 15)) {
    if ((u32)(up & 15) >= (u8)level) result += 1;
    if ((u32)(down & 15) >= (u8)level) result += 1;
    if ((u32)(pixel & 0xF0) >= (u8)high) result += 1;
    if ((u32)(right & 0xF0) >= (u8)high) result += 1;
  }
  return result;
}
