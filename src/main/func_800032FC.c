/* @header
 * func_800032FC
 * VRAM 0x800032FC | ROM 0x3EFC | size 0x40
 * asm: asm/nonmatchings/main/func_800032FC.s
 */
#include "common.h"

s32 MusStop(s32, s32);
s32 MusAsk(s32);
s32 osAfterPreNMI();

/* Stop audio channel 3 and wait for the channel and the mixer to drain. */
void func_800032FC(void) {
    MusStop(3, 0xA);
    do {

    } while (MusAsk(3) != 0);
    do {

    } while (osAfterPreNMI() != 0);
}
