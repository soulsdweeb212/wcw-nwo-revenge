#include "common.h"

s32 func_80014064(s32, s16);
extern s32 D_800482D4;

/* Forward arg0 to func_80014064 with the current context D_800482D4. */
void func_8000327C(s16 arg0) {
    func_80014064(D_800482D4, arg0);
}
