/* @header
 * func_8009C010
 * VRAM 0x8009C010 | ROM 0x48780 | size 0x208
 * asm: asm/nonmatchings/code_80090000/func_8009C010.s
 */
#include "common.h"

typedef struct {
    u32 w0, w1;   /* one two-word display-list command */
} Gfx0983;

extern s16 D_800C9818[];   /* keyframe table: 8 s16 per rect; t == 0x100 selects the final keyframe */

/* Append an interpolated textured rect to a display list: read/lerp the four
 * texture coordinates from the D_800C9818 keyframe table (frac 0x100 = final
 * keyframe), emit the four texture-coordinate commands and five tile commands,
 * then advance the caller's cursor. */
void func_8009C010(Gfx0983 **dlCursor, s32 rectIdx, s32 frac) {
    Gfx0983 *dl = *dlCursor;
    s32 base;
    s32 tex0;
    s32 tex1;
    s32 anim0;
    s32 anim1;

    base = rectIdx << 2;
    tex0 = D_800C9818[base];
    tex1 = D_800C9818[base + 2];
    if (frac == 0x100) {
        anim0 = D_800C9818[base + 1];
        anim1 = D_800C9818[base + 3];
    } else {
        anim0 = D_800C9818[base + 5] + (D_800C9818[base + 1] - D_800C9818[base + 5]) * frac / 256;
        anim1 = D_800C9818[base + 7] + (D_800C9818[base + 3] - D_800C9818[base + 7]) * frac / 256;
    }
    {
        Gfx0983 *q = dl++;
        q->w0 = 0x02180000;
        q->w1 = (((u32)anim0 << 18) >> 16) | (tex1 << 18);
    }
    {
        Gfx0983 *q = dl++;
        q->w0 = 0x02180002;
        q->w1 = (((u32)anim0 << 18) >> 16) | (tex0 << 18);
    }
    {
        Gfx0983 *q = dl++;
        q->w0 = 0x02180004;
        q->w1 = (((u32)anim1 << 18) >> 16) | (tex1 << 18);
    }
    {
        Gfx0983 *q = dl++;
        q->w0 = 0x02180006;
        q->w1 = (((u32)anim1 << 18) >> 16) | (tex0 << 18);
    }
    {
        Gfx0983 *q = dl++;
        q->w0 = 0x02140000;
        q->w1 = 0;
    }
    {
        Gfx0983 *q = dl++;
        q->w0 = 0x02140002;
        q->w1 = 0x08000000;
    }
    {
        Gfx0983 *q = dl++;
        q->w0 = 0x02140004;
        q->w1 = 0x800;
    }
    {
        Gfx0983 *q = dl++;
        q->w0 = 0x02140006;
        q->w1 = 0x08000800;
    }
    {
        Gfx0983 *q = dl++;
        q->w0 = 0x07000206;
        q->w1 = 0x604;
    }
    *dlCursor = dl;
}
