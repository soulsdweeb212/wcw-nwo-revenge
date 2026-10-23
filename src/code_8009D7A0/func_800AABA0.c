#include "common.h"

s32 func_800AB1B0();
s32 func_800AB2B4();
s32 func_800AB43C();
s32 func_800AD958(s32);

/* Request action 0x15 when none of the three sub-checks report success. */
void func_800AABA0(void) {
    if (((func_800AB1B0() << 0x18) == 0) && ((func_800AB2B4() << 0x18) == 0) && ((func_800AB43C() << 0x18) == 0)) {
        func_800AD958(0x15);
    }
}
