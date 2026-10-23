#include "common.h"

s32 func_80013B58(s32, s32);
s32 func_80013C24(s32);
s32 func_80025F10();

/* Stop audio channel 3 and wait for the channel and the mixer to drain. */
void func_800032FC(void) {
    func_80013B58(3, 0xA);
    do {

    } while (func_80013C24(3) != 0);
    do {

    } while (func_80025F10() != 0);
}
