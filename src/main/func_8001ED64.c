/* @header
 * func_8001ED64
 * VRAM 0x8001ED64 | ROM 0x1F964 | size 0x280
 * asm: asm/nonmatchings/main/func_8001ED64.s
 */
#include "common.h"

typedef struct { f64 v[8]; } Nw2F64x8;
extern u8 D_8003B780[];

static inline f64 _frexpf(f64 value, s32 *eptr)
{
    f64 absvalue;

    *eptr = 0;
    if (value == 0.0)
        return value;
    absvalue = (value > 0.0) ? value : -value;
    for (; absvalue >= 1.0; absvalue *= 0.5)
        ++*eptr;
    for (; absvalue < 0.5; absvalue += absvalue)
        --*eptr;
    return (value > 0.0 ? absvalue : -absvalue);
}

s16 func_8001ED64(f64 vol, f64 tgt, s32 count, u16 *ratel)
{
    s16 s;
    f64 invn = 1.0 / count, eps, a, fs, mant;
    s32 i_invn, ex, indx;
    f64 _lookupl[8];

    if (count == 0) {
        if (tgt >= vol) {
            *ratel = 0xffff;
            return 0x7fff;
        } else {
            *ratel = 0;
            return 0;
        }
    }

    if (tgt < 1.0)
        tgt = 1.0;
    if (vol <= 0)
        vol = 1;

    *(Nw2F64x8 *)_lookupl = *(Nw2F64x8 *)D_8003B780;
    eps = tgt / vol;
    i_invn = (s32)(invn * 1073741824.0);
    mant = _frexpf(eps, &ex);
    indx = (s32)(mant * 16);
    fs = (_lookupl[indx - 8] + ex) * 0.69314718055994529 / 1073741824.0 + 1.0;
    a = 1.0;
    while (i_invn) {
        if (i_invn & 1)
            a *= fs;
        i_invn >>= 1;
        fs *= fs;
    }
    a *= a;
    a *= a;
    a *= a;
    s = (s16)a;
    *ratel = (s16)(0xffff * (a - (f32)s));
    return s;
}
