/* @header
 * buildVertexDisplayList  (originally func_800046F0)
 * VRAM 0x800046F0 | ROM 0x52F0 | size 0x17C
 * asm: asm/nonmatchings/main/buildVertexDisplayList.s
 */
#include "common.h"

/*
 * Emit the display list for `obj->vertexCount` vertices read from `vertices`
 * starting at `obj->vertexOffset`.  Each Gfx word pair packs two vertices;
 * RGB components are doubled (5-bit -> 6-bit shift) on the way.
 */
typedef struct {
    u8 pad0;
    s8 vertexCount;
    s8 vertexOffset;
    u8 pad3[0x11];
    void *displayList;
} Nw2VertexBatch;

typedef struct {
    u32 w0, w1;
} Nw2Gfx;

void buildVertexDisplayList(Nw2VertexBatch *obj, u8 *vertices) {
    Nw2Gfx *g;
    u8 *v;
    u32 i;

    g = (Nw2Gfx *)obj->displayList;
    v = vertices + (obj->vertexOffset * 8 + 8);
    {
        Nw2Gfx *q = g++;
        q->w0 = 0xD9FFF9FF;
        q->w1 = 0;
    }
    {
        Nw2Gfx *q = g++;
        q->w0 = 0xD9FFFFFF;
        q->w1 = 0x400;
    }
    for (i = 0; i < obj->vertexCount - 1; i += 2) {
        Nw2Gfx *q = g++;
        q->w0 = (((v[0] * 2) & 0xFF) << 16) | ((v[1] << 9) & 0xFE00) | ((v[2] * 2) & 0xFF) | 0x06000000;
        q->w1 = (((v[3] * 2) & 0xFF) << 16) | ((v[4] << 9) & 0xFE00) | ((v[5] * 2) & 0xFF);
        v += 6;
    }
    if (i < obj->vertexCount) {
        Nw2Gfx *q = g++;
        q->w0 = (((v[0] * 2) & 0xFF) << 16) | ((v[1] << 9) & 0xFE00) | ((v[2] * 2) & 0xFF) | 0x05000000;
        q->w1 = 0;
    }
    {
        Nw2Gfx *q = g++;
        q->w0 = 0xE7000000;
        q->w1 = 0;
    }
    {
        Nw2Gfx *q = g++;
        q->w0 = 0xDF000000;
        q->w1 = 0;
    }
}
