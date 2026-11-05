/* @header
 * osAiGetStatus  (originally func_80020A90)
 * VRAM 0x80020A90 | ROM 0x21690 | size 0x10
 * asm: asm/nonmatchings/main/osAiGetStatus.s
 */
/* SDK: libultra 2.0I, ultralib src/io/aigetstat.c (same code as the SDK source). */
#include "common.h"

extern u8 hdwrBugFlag;

s32 osVirtualToPhysical(s32);
s32 __osAiDeviceBusy(void);
s32 alLink(s32, void *);
s32 alUnlink(s32);

s32 osAiGetStatus(void) {
    return *(vu32 *)0xA450000C;
}
