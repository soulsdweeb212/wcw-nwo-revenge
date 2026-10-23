#include "common.h"

/* func_80099748: appends a full-screen (480x240) single-colour fill to the
 * display list at *out, advancing *out past it. Each of the 4-row strips is a
 * RDP rectangle command (0xE4) with a scissor (0xE1) and tile-size (0xF1)
 * pair, preceded by a sync command (0xE7) and the fill colour (0xFA). The
 * r/g/b/a arguments are the fill colour components. */
typedef union { struct { u32 w0, w1; } words; u64 align; } Gfx99748;
#define EMIT99748(a, b) { Gfx99748 *_g = p++; _g->words.w0 = (a); _g->words.w1 = (b); }

void func_80099748(Gfx99748 **out, s32 r, s32 g, s32 b, s32 a) {
    Gfx99748 *p = *out;
    Gfx99748 **pp;
    s32 y, end;
    s32 width = 479, height;

    EMIT99748(0xE7000000, 0);
    EMIT99748(0xFCFFFFFF, 0xFFFDF6FB);
    EMIT99748(0xFA000000, (r << 24) | ((g & 255) << 16) | ((b & 255) << 8) | (a & 255));
    pp = &p;
    height = 239;
    y = 0;
    {
        Gfx99748 *q = p;
        s32 x = 0;
        u32 *w;

        q->words.w0 = 0xE7000000;
        q->words.w1 = 0;
        q++;
        w = (u32 *)q - 1;
        do {
            end = y + 4;
            if (end > height) {
                end = height;
            }
            w += 2;
            w[-1] = 0xE4000000 | (((width << 2) & 0xFFF) << 12) | ((end << 2) & 0xFFF);
            w[0] = (((x << 2) & 0xFFF) << 12) | ((y << 2) & 0xFFF);
            q++;
            w += 2;
            w[-1] = 0xE1000000;
            w[0] = 0;
            q++;
            w += 2;
            w[-1] = 0xF1000000;
            w[0] = 0x04000400;
            q++;
            y += 4;
        } while (y < height);
        { Gfx99748 *_g = q++; _g->words.w0 = 0xE7000000; _g->words.w1 = 0; }
        *pp = q;
    }
    *out = p;
}
