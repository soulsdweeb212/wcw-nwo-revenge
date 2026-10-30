/* @header
 * func_800AABA0
 * VRAM 0x800AABA0 | ROM 0x9E040 | size 0x58
 * asm: asm/nonmatchings/code_8009D7A0/func_800AABA0.s
 */
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
