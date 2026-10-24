#include "common.h"

typedef struct {u8 p0[0x48];s32 f48,f4C;u8 p50[0x4c];s32 f9C;u8 pA0[4];s32 fA4,fA8;u8 pAC[0x16];s16 fC2,fC4;} V16784;
s32 func_80016784(V16784 *v, u8 *p) {
    s32 x, y;
    x = *p++ << 8; x += *p++;
    y = *p++ << 8; y += *p++;
    v->fC2 = 1;
    v->f4C = v->fA8 + y;
    y = *p++ << 8; y += *p++;
    v->fC4 = 1;
    v->f48 = v->fA4 + y;
    return v->f9C + x;
}
