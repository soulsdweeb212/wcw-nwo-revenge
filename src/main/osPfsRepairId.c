/* @header
 * osPfsRepairId  (originally func_80025280)
 * VRAM 0x80025280 | ROM 0x25E80 | size 0x58
 * asm: asm/nonmatchings/main/osPfsRepairId.s
 */
/* SDK: libultra 2.0I, ultralib src/io/pfsrepairid.c (same code as the SDK source). */
#include "common.h"

s32 __osGetId(void*);
/* If the Pak status has a pending bit (1 or 4), read its ID and clear the retry bit
 * on success; otherwise report status 5. */
s32 osPfsRepairId(s32 *p){s32 r;if(*p&5){r=__osGetId(p);if(r==0)*p&=~4;}else r=5;return r;}
