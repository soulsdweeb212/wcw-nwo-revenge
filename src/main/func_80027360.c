#include "common.h"

s32 func_80027360(void) {
    return (*(vu32 *)0xA4040010 & 0x1C) != 0;
}

extern s32 D_8007BD60;
s32 nw2DisableInterrupts(void);
s32 func_80026AF0(void);
void nw2RestoreInterrupts(s32);
void func_80028100(s32, s32);
