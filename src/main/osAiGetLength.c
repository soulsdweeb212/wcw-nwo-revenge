/* @header
 * osAiGetLength  (originally func_80020A80)
 * VRAM 0x80020A80 | ROM 0x21680 | size 0x10
 * asm: asm/nonmatchings/main/osAiGetLength.s
 */
/* SDK: libultra 2.0I, ultralib src/io/aigetlen.c (same code as the SDK source). */
#include "common.h"

extern u8 hdwrBugFlag;

s32 osVirtualToPhysical(s32);
s32 __osAiDeviceBusy(void);
s32 alLink(s32, void *);
s32 alUnlink(s32);

s32 osAiGetLength(void) {
    return *(vu32 *)0xA4500004;
}
