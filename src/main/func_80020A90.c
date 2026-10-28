#include "common.h"

extern u8 D_80037520;

s32 func_8001CE80(s32);
s32 ai_is_busy(void);
s32 func_8002021C(s32, void *);
s32 func_8002023C(s32);

s32 func_80020A90(void) {
    return *(vu32 *)0xA450000C;
}
