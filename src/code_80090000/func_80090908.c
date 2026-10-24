#include "common.h"

typedef struct { u32 w0; u32 w1; } Gfx0908;

typedef struct {
    u16 count;
    u16 f2;
    u8 pad4[4];
    union { u16 h; u8 b[2]; } f8;
    u16 fA;
    u16 fC;
    u16 fE;
    u8 f10;
    u8 f11;
    u8 f12;
    u8 f13;
    u8 f14[1];
} S0908;

extern Gfx0908 *D_800DB68C;
extern s32 D_800DB69C;
extern s32 D_800DB6A0;
u8 *func_800B64EC(s32, u16);
u32 func_8001CE80(s32);

#define EMIT(a, b) { Gfx0908 *_g = D_800DB68C++; _g->w0 = (a); _g->w1 = (b); }
#define TRI(f, t) \
    ((f) == 0 ? (((t[0] * 2) & 0xFF) << 16) | ((t[1] << 9) & 0xFE00) | ((t[2] * 2) & 0xFF) : \
     (f) == 1 ? (((t[1] * 2) & 0xFF) << 16) | ((t[2] << 9) & 0xFE00) | ((t[0] * 2) & 0xFF) : \
                (((t[2] * 2) & 0xFF) << 16) | ((t[0] << 9) & 0xFE00) | ((t[1] * 2) & 0xFF))
#define TILEW1(tile, s) (((tile) << 24) | ((s->f12 & 3) << 18) | ((s->f13 & 0xF) << 14) | ((s->f10 & 3) << 8) | ((s->f11 & 0xF) << 4))
#define LOADBLOCK(shift, rnd, rsh) { \
    Gfx0908 *_g = D_800DB68C++; \
    u32 _w; u32 _dw; s32 _dxt; s32 _lrs; u32 _hi; u32 _v; \
    _g->w0 = 0xF3000000; \
    _w = s->fC; \
    _dw = _w >> (shift); \
    _dxt = _dw != 0 ? _dw + 0x7FF : 0x800; \
    _lrs = ((s32)(_w * s->fE + (rnd)) >> (rsh)) - 1; \
    if (_lrs >= 0x800) { \
        _lrs = 0x7FF; \
    } \
    _hi = ((_lrs & 0xFFF) << 12) | 0x07000000; \
    if (_dw != 0) { \
        _v = _hi | ((_dxt / (s32)_dw) & 0xFFF); \
    } else { \
        _v = _hi | (_dxt & 0xFFF); \
    } \
    _g->w1 = _v; \
}

void func_80090908(S0908 *s, s32 arg1)
{
    u8 *tri;
    u8 *pal;
    u8 *tex;
    u8 *pr;
    s32 i;
    s32 k;

    tri = func_800B64EC(D_800DB6A0, s->f2);
    pal = func_800B64EC(D_800DB69C, s->f8.b[1]) + 8;
    tex = func_800B64EC(D_800DB69C, s->fA);
    EMIT(0xE7000000, 0);
    EMIT(0xE3001001, 0x8000);
    if (s->f8.h & 0x8000) {
        EMIT(0xFD100000, (u32)tex - 0x80000000);
        EMIT(0xE8000000, 0);
        EMIT(0xF5000100, 0x07000000);
        EMIT(0xE6000000, 0);
        EMIT(0xF0000000, 0x073FC000);
        EMIT(0xE7000000, 0);
        EMIT(0xFD500000, (u32)pal - 0x80000000);
        EMIT(0xF5500000, TILEW1(7, s));
        EMIT(0xE6000000, 0);
        LOADBLOCK(3, 1, 1);
        EMIT(0xE7000000, 0);
        EMIT(0xF5480000 | ((((s->fC + 7) >> 3) & 0x1FF) << 9), TILEW1(0, s));
        EMIT(0xF2000000, ((((s->fC - 1) * 4) & 0xFFF) << 12) | (((s->fE - 1) * 4) & 0xFFF));
    } else {
        EMIT(0xFD100000, (u32)tex - 0x80000000);
        EMIT(0xE8000000, 0);
        EMIT(0xF5000100, 0x07000000);
        EMIT(0xE6000000, 0);
        EMIT(0xF0000000, 0x0703C000);
        EMIT(0xE7000000, 0);
        EMIT(0xFD500000, (u32)pal - 0x80000000);
        EMIT(0xF5500000, TILEW1(7, s));
        EMIT(0xE6000000, 0);
        LOADBLOCK(4, 3, 2);
        EMIT(0xE7000000, 0);
        EMIT(0xF5400000 | (((((s->fC >> 1) + 7) >> 3) & 0x1FF) << 9), TILEW1(0, s));
        EMIT(0xF2000000, ((((s->fC - 1) * 4) & 0xFFF) << 12) | (((s->fE - 1) * 4) & 0xFFF));
    }
    pr = s->f14;
    k = 0;
    EMIT(0xE7000000, 0);
    for (i = 0; i < s->count; i++, tri += 4) {
        if (pr[1] == i) {
            Gfx0908 *gv = D_800DB68C++;
            gv->w0 = 0x01000000 | (pr[0] << 12) | ((pr[0] & 0x7F) << 1);
            gv->w1 = func_8001CE80(arg1 + k * 16);
            k += pr[0];
            pr += 2;
        }
        if (i + 1 < s->count && i + 1 != pr[1]) {
            Gfx0908 *gt = D_800DB68C++;
            gt->w0 = TRI(tri[3], tri) | 0x06000000;
            gt->w1 = TRI(tri[7], (tri + 4));
            i++;
            tri += 4;
        } else {
            Gfx0908 *gt = D_800DB68C++;
            gt->w0 = TRI(tri[3], tri) | 0x05000000;
            gt->w1 = 0;
        }
    }
}
