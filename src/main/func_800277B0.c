#include "common.h"

s32 func_8001CAC0(void *, s32, s32);
extern s32 D_8007E210;

/* Post a zero message to the D_8007E210 message queue without waiting. */
void func_800277B0(void) {
    func_8001CAC0(&D_8007E210, 0, 0);
}
