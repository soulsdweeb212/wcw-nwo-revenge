#include "common.h"

extern s8 D_800706A4[];
extern s8 D_800485B0[];
extern s8 D_800485D0[];
extern u8 D_800517D0[];

void setIndexedS16Pair(s32, s32, s8, s8);
void func_80001DC4(void *);
void buildEntityPartTransforms(void *, s32, f32, f32);

s8 func_8000B710(s32 arg0) {
    return D_800706A4[(s16)arg0];
}

void func_8000B2B8(s32 arg0) {
    s16 a0 = (s16)arg0;
    s8 *baseA = D_800485B0 + a0 * 8;
    s8 *baseB = D_800485D0 + a0 * 8;
    s32 i = 0;

    do {
        s8 *p = baseA + (s16)i;
        s8 v = *p;

        if (v >= 0) {
            setIndexedS16Pair(a0, 0, baseB[(s16)i], v);
            *p = -1;
        }
        i++;
    } while (i < 8U);
}

void func_8000B248(s32 arg0, s32 arg1) {
    s8 *p = D_800485B0 + (s16)arg0 * 8 + (s16)arg1;
    s8 v = *p;

    if (v >= 0) {
        setIndexedS16Pair((s16)arg0, 0, D_800485D0[(s16)arg0 * 8 + (s16)arg1], v);
        *p = -1;
    }
}

void func_8000CD18(s32 arg0, f32 arg1, f32 arg2) {
    u8 *p = D_800517D0 + (s16)arg0 * 0x13C4;

    buildEntityPartTransforms(p, (s16)arg0, arg1, arg2);
    func_80001DC4(p);
}
