#include "common.h"

extern u8 D_80037520;

s32 func_8001CE80(s32);
s32 ai_is_busy(void);
s32 func_8002021C(s32, void *);
s32 func_8002023C(s32);

s32 func_80020A80(void) {
    return *(vu32 *)0xA4500004;
}

s32 func_80020A90(void) {
    return *(vu32 *)0xA450000C;
}

s32 func_80020AA0(s32 arg0, s32 arg1) {
    s32 a;
    s32 result;

    a = arg0;
    if (D_80037520 != 0) {
        a -= 0x2000;
    }
    if (((arg0 + arg1) & 0x1FFF) == 0) {
        D_80037520 = 1;
    } else {
        D_80037520 = 0;
    }
    if (ai_is_busy() != 0) {
        return -1;
    }
    result = func_8001CE80(a);
    *(s32 *)0xA4500000 = result;
    *(s32 *)0xA4500004 = arg1;
    return 0;
}

void func_80020800(u8 *arg0) {
    s32 s0;

    s0 = *(s32 *)(arg0 + 0x14);
    if (s0 != 0) {
        do {
            func_8002023C(s0);
            func_8002021C(s0, arg0 + 4);
            s0 = *(s32 *)(arg0 + 0x14);
        } while (s0 != 0);
    }
}
