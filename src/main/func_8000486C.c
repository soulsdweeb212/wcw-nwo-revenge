#include "common.h"

typedef struct { s16 x,y,z,flag,s,t; u8 r,g,b,a; } V;
/* Decodes a packed vertex list (header: scale, count, base x/y/z, s/t bits)
 * into an array of V records: positions are scaled and offset, texture coords
 * are derived from the header bits plus the packed per-vertex nibbles, and each
 * vertex gets its RGBA with alpha 255. */
void func_8000486C(V *o, u8 *src) {
    s8 *p; u32 i; u16 s, t; s32 scale; s16 x, y, z; V *v;
    p = (s8 *)src + 8;
    scale = src[0] + 1;
    x = (src[4] << 24) >> 20;
    y = (src[5] << 24) >> 20;
    z = (src[6] << 24) >> 20;
    s = src[7] & 0xF0;
    t = (src[7] << 4) & 0xF0;
    v = o;
    for (i = 0; i < src[1]; i++) {
        v->x = (p[0] + x) * scale;
        v->y = (p[1] + y) * scale;
        v->z = (p[2] + z) * scale;
        v->flag = 0;
        v->s = (((u8)p[3] + s) << 5) + 8;
        v->t = (((u8)p[4] + t) << 5) + 8;
        v->r = p[5]; v->g = p[6]; v->b = p[7]; v->a = 255;
        p += 8; v++;
    }
}
