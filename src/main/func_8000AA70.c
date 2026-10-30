/* @header
 * func_8000AA70
 * VRAM 0x8000AA70 | ROM 0xB670 | size 0x290
 * asm: asm/nonmatchings/main/func_8000AA70.s
 */
#include "common.h"

typedef struct { f32 x, y, z; } VecAA70;
extern VecAA70 D_80048590;

u8 *func_8000AA70(u8 *p, f32 *out, VecAA70 *vec)
{
    s32 x, y, z;
    s32 hasVec, absVec;

    x = *p++;
    x <<= 8;
    x |= *p++;
    x <<= 8;
    x |= *p++;
    x <<= 8;
    x |= *p++;
    y = x >> 10;
    z = x >> 20;
    hasVec = x & 0x80000000;
    absVec = x & 0x40000000;
    x &= 0x3FF;
    out[0] = (f32)x * 0.3515625;
    y &= 0x3FF;
    out[1] = (f32)y * 0.3515625;
    z &= 0x3FF;
    out[2] = (f32)z * 0.3515625;
    if (hasVec) {
        if (absVec) {
            s32 s;
            x = *p++;
            y = *p++;
            z = *p++;
            s = x & 0x80;
            x &= 0x7F;
            if (s) {
                x = -x;
            }
            s = y & 0x80;
            y &= 0x7F;
            if (s) {
                y = -y;
            }
            s = z & 0x80;
            z &= 0x7F;
            if (s) {
                z = -z;
            }
            vec->x = x;
            vec->y = y;
            vec->z = z;
            vec->x = vec->x * 0.5;
            vec->y = vec->y * 0.5;
            vec->z = vec->z * 0.5;
            vec->x += D_80048590.x;
            vec->y += D_80048590.y;
            vec->z += D_80048590.z;
        } else {
            s32 s;
            x = *p++;
            x <<= 8;
            x |= *p++;
            x <<= 8;
            x |= *p++;
            x <<= 8;
            x |= *p++;
            y = x >> 11;
            z = x >> 22;
            s = x & 0x400;
            x &= 0x3FF;
            if (s) {
                x = -x;
            }
            s = y & 0x400;
            y &= 0x3FF;
            if (s) {
                y = -y;
            }
            s = z & 0x200;
            z &= 0x1FF;
            if (s) {
                z = -z;
            }
            vec->x = x;
            vec->y = y;
            vec->z = z;
            D_80048590.x = vec->x;
            D_80048590.y = vec->y;
            D_80048590.z = vec->z;
        }
    }
    return p;
}
