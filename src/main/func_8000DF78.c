#include "common.h"

s32 func_8000335C();
s32 func_80013CA4(s32, s32);

/* When the current track is nonzero, release audio resource arg0 at level 2. */
void func_8000DF78(s32 arg0) {
    if ((func_8000335C() << 0x10) != 0) {
        func_80013CA4(arg0, 2);
    }
}
