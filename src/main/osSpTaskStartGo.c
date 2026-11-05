/* @header
 * osSpTaskStartGo  (originally func_80020D4C)
 * VRAM 0x80020D4C | ROM 0x2194C | size 0x2C
 * asm: asm/nonmatchings/main/osSpTaskStartGo.s
 */
/* SDK: libultra 2.0I, ultralib src/io/sptask.c (same code as the SDK source). */
#include "common.h"

s32 __osSpDeviceBusy();
s32 __osSpSetStatus(s32);

/* Wait for the RDP to become idle, then acknowledge its interrupt (0x125). */
void osSpTaskStartGo(void) {
    do {

    } while (__osSpDeviceBusy() != 0);
    __osSpSetStatus(0x125);
}
