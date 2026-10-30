/* @header
 * func_80029A24
 * VRAM 0x80029A24 | ROM 0x2A624 | size 0x21C
 * asm: asm/nonmatchings/main/func_80029A24.s
 */
#include "common.h"

extern u8 D_80038E4C[]; extern u8 D_80038E5C[]; extern u8 D_8003BAB0[]; extern u8 D_8003BAB4[]; extern u8 D_8003BAB8[]; extern u8 D_8003BAC0[];

static inline u8 *copyStr80029A24(u8 *dst, u8 *src) {
    while (1) {
        *dst = *src;
        if (*src++ == 0) break;
        dst++;
    }
    return dst;
}

static inline u8 *appendSuffix80029A24(u8 *dst, s32 mode) {
    u8 *src;

    switch (mode & 0x3000) {
    case 0x1000: src = D_8003BAB0; break;
    case 0x2000: src = D_8003BAB4; break;
    case 0x3000: src = D_8003BAB8; break;
    default: src = D_8003BAC0; break;
    }
    dst = copyStr80029A24(dst, src);
    return dst;
}

u8 *func_80029A24(u8 *out, s32 val, s32 flags) {
    s32 scale;
    s32 tmp;
    s32 d;
    s32 mode;

    if (val & 0x200000) {
        val = -val & 0x3FFFFF;
        *out++ = '-';
    }
    *out = '0';
    scale = 1;
    tmp = val / 10;
    mode = flags & 0xFFFF;
    while (tmp > 0) {
        scale *= 10;
        tmp /= 10;
    }
    if ((mode & 0x3000) == 0x2000 && scale == 1) {
        scale = 10;
    }
    while (scale != 0) {
        d = (val / scale) % 10;
        if (scale < 10 && (flags & 0x3000) == 0x2000) {
            *out++ = D_80038E5C[0];
        }
        out[0] = D_80038E4C[d];
        out[1] = 0;
        scale /= 10;
        out++;
    }
    if (flags & 0x3000) {
        out = appendSuffix80029A24(out, (u16)flags);
    }
    return out;
}
