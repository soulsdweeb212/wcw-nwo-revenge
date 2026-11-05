/* @header
 * func_8000DF78
 * VRAM 0x8000DF78 | ROM 0xEB78 | size 0x38
 * asm: asm/nonmatchings/main/func_8000DF78.s
 */
#include "common.h"

s32 func_8000335C();
s32 MusHandleStop(s32, s32);

/* When the current track is nonzero, release audio resource arg0 at level 2. */
void func_8000DF78(s32 arg0) {
    if ((func_8000335C() << 0x10) != 0) {
        MusHandleStop(arg0, 2);
    }
}
