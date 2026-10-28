#include "common.h"

/* identical to func_80017F44 (matched), with its names changed by decompdecomp */
extern s32 *D_80037510;

s32 *func_80017F18(void);
s32 func_80018C24(s32 *arg0, s32 arg1, s32 *arg2);
s32 func_80018660(s32 arg0, s32 arg1, s32 arg2);

void func_800207E8(s32 *arg0) {
    s32 *v1 = D_80037510;
    *arg0 = *(s32 *)((u8 *)v1 + 0x2C);
    *(s32 *)((u8 *)v1 + 0x2C) = (s32)arg0;
}
