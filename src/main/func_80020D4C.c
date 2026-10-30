/* @header
 * func_80020D4C
 * VRAM 0x80020D4C | ROM 0x2194C | size 0x2C
 * asm: asm/nonmatchings/main/func_80020D4C.s
 */
#include "common.h"

s32 func_80027360();
s32 func_80027390(s32);

/* Wait for the RDP to become idle, then acknowledge its interrupt (0x125). */
void func_80020D4C(void) {
    do {

    } while (func_80027360() != 0);
    func_80027390(0x125);
}
