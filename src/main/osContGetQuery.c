/* @header
 * osContGetQuery  (originally func_80021210)
 * VRAM 0x80021210 | ROM 0x21E10 | size 0x20
 * asm: asm/nonmatchings/main/osContGetQuery.s
 */
/* SDK: libultra 2.0I, ultralib src/io/contquery.c (same code as the SDK source). */
#include "common.h"

s32 __osContGetInitData(void *, s32);

/* Build the RDP command for arg0 into a scratch local. */
void osContGetQuery(s32 arg0) {
    s32 sp10;

    __osContGetInitData(&sp10, arg0);
}
