#include "common.h"

typedef struct { u32 w0, w1; } G773;
extern u8 D_C95B8[];
extern f64 D_800D6078;
extern f64 D_800D6080;
f32 sinf(f32);
void func_80096A6C(G773 **, void *, s32, s32, s32, s32, s32, s32, s32);

#define CMD(c, a, b) { G773 *_g = gfx++; _g->w0 = (u32)(a); _g->w1 = (u32)(b); }

#define SHL(v, s, w) ((u32)(((u32)(v) & ((1 << (w)) - 1)) << (s)))
#define MV2(pkt, vtx, where, val) { G773 *_g = (G773 *)(pkt); _g->w0 = SHL(2, 24, 8) | SHL((where), 16, 8) | SHL((vtx) * 2, 0, 16); _g->w1 = (u32)(val); }
#define MV(vtx, where, val) MV2(gfx++, vtx, where, val)

void func_8009773C(G773 **gfxp, void *tex, s32 fmt, s32 phase, s32 x, s32 y, s32 w, s32 h, s32 dw, s32 dh, s32 texw,
                   s32 amp0, s32 amp1, s32 freq)
{
    G773 *gfx = *gfxp;
    f32 sx, sy;
    s32 t, s;
    s32 rows = 4;
    s32 cols = 0xF0;
    s32 uls, ult, lrs, lrt, s1, t1;
    f32 yt, yb, xl, xr;
    s32 off0, off1;
    s32 n;
    u32 lo, lo1, hi0, hi1;
    f32 sn;

    sy = (f64)dh / h;
    sx = (f64)dw / w;
    t = 0;
    CMD(0, 0xDE000000, D_C95B8);
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
        sn = sinf(((s32)((phase + yt - y) * freq) & 0x3FF) * 360 * D_800D6078);
        off0 = (amp0 + (f32)(amp1 - amp0) * (yt - y) / dh) * sn;
        sn = sinf(((s32)((phase + yb - y) * freq) & 0x3FF) * 360 * D_800D6080);
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
            CMD(0, 0xE7000000, 0);
            func_80096A6C(&gfx, tex, fmt, texw, h, uls, ult, lrs, lrt);
            MV(0, 0x18, SHL((s32)((yt) * 4.0f), 0, 16) | SHL((s32)((xl + off0) * 4.0f), 16, 16));
            MV(1, 0x18, SHL((s32)((yt) * 4.0f), 0, 16) | SHL((s32)((xr + off0) * 4.0f), 16, 16));
            MV(2, 0x18, SHL((s32)((yb) * 4.0f), 0, 16) | SHL((s32)((xl + off1) * 4.0f), 16, 16));
            MV(3, 0x18, SHL((s32)((yb) * 4.0f), 0, 16) | SHL((s32)((xr + off1) * 4.0f), 16, 16));
            hi0 = (u32)s << 21;
            hi1 = (u32)s1 << 21;
            lo = (u32)t << 21 >> 16;
            MV(0, 0x14, lo | hi0);
            lo |= hi1;
            MV(1, 0x14, lo);
            lo1 = (u32)t1 << 21 >> 16;
            MV(2, 0x14, lo1 | hi0);
            lo1 |= hi1;
            MV(3, 0x14, lo1);
            { G773 *_g = gfx++; _g->w0 = 0x07000206; _g->w1 = 0x604; }
        }
    }
    *gfxp = gfx;
}
