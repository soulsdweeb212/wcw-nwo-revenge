#include "common.h"

s32 func_80027380(void) {
    return *(vu32 *)0xA4040010;
}

s32 func_80027360(void) {
    return (*(vu32 *)0xA4040010 & 0x1C) != 0;
}

s32 ai_is_busy(void) {
    return *(vu32 *)0xA450000C < 0;
}

extern s32 D_8007BD60;
s32 nw2DisableInterrupts(void);
s32 func_80026AF0(void);
void nw2RestoreInterrupts(s32);
void func_80028100(s32, s32);

void programTimerCountdown(s32 arg0, s32 arg1) {
    s32 s;
    s32 v;

    s = nw2DisableInterrupts();
    v = func_80026AF0();
    D_8007BD60 = v;
    func_80028100(arg1 + v, v);
    nw2RestoreInterrupts(s);
}
