#include "common.h"

s32 func_80000EE0();
s32 func_8001CAC0(s32, s32, s32);

/* Send message arg0 (blocking) to the current event queue. */
void func_800005D0(s32 arg0) {
    func_8001CAC0(func_80000EE0(), arg0, 1);
}
