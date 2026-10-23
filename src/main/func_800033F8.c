#include "common.h"

s32 func_80013C24(s32);

/* Report whether audio channel 2 is still busy. */
s32 func_800033F8(void) {
    return func_80013C24(2) != 0;
}
