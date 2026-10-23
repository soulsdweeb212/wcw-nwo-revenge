#include "common.h"

/* func_80013260: parses one animation descriptor for the entity arg0. It
 * decodes a variable-length id (7 bits, extended by a following byte when the
 * high bit is set), looks the record up through the entity's table at +0x94,
 * and fills the animation fields: length (+0xDF), playback rate (+0x84),
 * the three frame counts (+0xE6/+0xE7/+0xE8) and their per-frame step rates
 * (+0x78/+0x7C/+0x80) derived from D_8003B320 and the frame spans. Returns the
 * advanced source pointer. */
#define F(o, t, x) (*(t *)((u8 *)(o) + (x)))
extern const f64 D_8003B320;

u8 *func_80013260(void *arg0, u8 *arg1) {
    s32 n, v;
    u8 *p;
    n = *arg1++;
    if (n & 0x80) {
        n &= 0x7F;
        n <<= 8;
        n |= *arg1++;
    }
    v = n * 7 + F(F(arg0, void *, 0x94), s32, 0x10);
    n = *(u8 *)(v | (v & ~v));
    p = (u8 *)(v | (v & ~v) | (v & ~v));
    if (n == 0)
        n = 1;
    F(arg0, u8, 0xDF) = n;
    F(arg0, s32, 0x84) = 0x400 / n;
    F(arg0, u8, 0xE0) = p[1];
    n = p[2];
    F(arg0, u8, 0xE6) = n;
    v = p[3];
    F(arg0, f32, 0x78) = (D_8003B320 / (f32)n) * (f32)(v - F(arg0, u8, 0xE0));
    F(arg0, u8, 0xE1) = v;
    n = p[4];
    F(arg0, u8, 0xE7) = n;
    v = p[5];
    F(arg0, f32, 0x7C) = (D_8003B320 / (f32)n) * (f32)(v - F(arg0, u8, 0xE1));
    F(arg0, u8, 0xE2) = v;
    n = p[6];
    F(arg0, u8, 0xE8) = n;
    F(arg0, f32, 0x80) = D_8003B320 / (f32)n;
    return arg1;
}
