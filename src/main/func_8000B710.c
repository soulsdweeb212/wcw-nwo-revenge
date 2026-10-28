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
