/* @header
 * func_8009773C
 * VRAM 0x8009773C | ROM 0x43EAC | size 0x6E0
 * asm: asm/nonmatchings/code_80090000/func_8009773C.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G773;
extern u8 D_C95B8[];
f32 sinf(f32);
/* 3.4088433159722225e-05 (0x3F01DF45A50DE271) is a double literal; the assembler's li.d puts each
 * copy in .rodata (0x800D6078, 0x800D6080). It is about pi/180/512, 1 ulp off 3.14159/92160. */
void func_80096A6C(G773 **, void *, s32, s32, s32, s32, s32, s32, s32);

#define SHL(v, s, w) ((u32)(((u32)(v) & ((1 << (w)) - 1)) << (s)))
/* No parentheses around b: the cast applies only to the first operand of b's `|`
 * (as in buildTiledTextureDisplayList). */
#define EMIT_X(a, b) { G773 *g = gfx++; g->w0 = (a); g->w1 = ((unsigned short)b); }

void func_8009773C(G773 **gfxp, void *tex, s32 fmt, s32 phase, s32 x, s32 y, s32 w, s32 h, s32 dw, s32 dh, s32 texw,
                   s32 amp0, s32 amp1, s32 freq)
{
    G773 *gfx = *gfxp;
    s32 off0, off1;
    f32 sy, sx;
    s32 t, s;
    s32 rows = 4;
    s32 cols = 0xF0;
    s32 uls, ult, lrs, lrt, s1, t1;
    f32 yt, yb, xl, xr;
    s32 n;
    f32 sn;

    sy = (f64)dh / h;
    sx = (f64)dw / w;
    t = 0;
    { G773 *g = gfx++; g->w0 = 0xDE000000; g->w1 = (u32)D_C95B8; }
    for (; t < h; t += rows) {
        ult = t - 1;
        if (ult < 0) ult = 0;
        lrt = t + rows;
        if (lrt > h - 1) lrt = h - 1;
        n = t + rows;
        t1 = n - 1;
        if (t1 > h - 1) t1 = h - 1;
        yb = (f32)y + n * sy;
        yt = (f32)y + t * sy;
        if (!(yb <= (f32)(y + dh))) yb = (f32)(y + dh);
        sn = sinf(((s32)((phase + yt - y) * freq) & 0x3FF) * 360 * 3.4088433159722225e-05);
        off0 = (amp0 + (f32)(amp1 - amp0) * (yt - y) / dh) * sn;
        sn = sinf(((s32)((phase + yb - y) * freq) & 0x3FF) * 360 * 3.4088433159722225e-05);
        off1 = (amp0 + (f32)(amp1 - amp0) * (yb - y) / dh) * sn;
        for (s = 0; s < w; s += cols) {
            uls = s - 1;
            if (uls < 0) uls = 0;
            lrs = s + cols;
            if (lrs > w - 1) lrs = w - 1;
            n = s + cols;
            s1 = n - 1;
            if (s1 > w - 1) s1 = w - 1;
            xr = (f32)x + n * sx;
            xl = (f32)x + s * sx;
            if (!(xr <= (f32)(x + dw))) xr = (f32)(x + dw);
            if ((xl < 0.0f) & (xr < 0.0f)) continue;
            if ((yt < 0.0f) & (yb < 0.0f)) continue;
            if ((480.0f <= xl) & (480.0f <= xr)) continue;
            if ((240.0f <= yt) & (240.0f <= yb)) continue;
            EMIT_X(0xE7000000, 0);
            func_80096A6C(&gfx, tex, fmt, texw, h, uls, ult, lrs, lrt);
            EMIT_X(0x02180000, SHL((s32)(yt * 4.0f), 0, 16) | SHL((s32)((xl + off0) * 4.0f), 16, 16));
            EMIT_X(0x02180002, SHL((s32)(yt * 4.0f), 0, 16) | SHL((s32)((xr + off0) * 4.0f), 16, 16));
            EMIT_X(0x02180004, SHL((s32)(yb * 4.0f), 0, 16) | SHL((s32)((xl + off1) * 4.0f), 16, 16));
            EMIT_X(0x02180006, SHL((s32)(yb * 4.0f), 0, 16) | SHL((s32)((xr + off1) * 4.0f), 16, 16));
            EMIT_X(0x02140000, ((u32)(t << 21) >> 16) | SHL(s << 5, 16, 16));
            EMIT_X(0x02140002, ((u32)(t << 21) >> 16) | SHL(s1 << 5, 16, 16));
            EMIT_X(0x02140004, ((u32)(t1 << 21) >> 16) | SHL(s << 5, 16, 16));
            EMIT_X(0x02140006, ((u32)(t1 << 21) >> 16) | SHL(s1 << 5, 16, 16));
            EMIT_X(0x07000206, 0x604);
        }
    }
    *gfxp = gfx;
}
