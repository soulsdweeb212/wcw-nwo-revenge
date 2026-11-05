/* @header
 * __osSiRelAccess  (originally func_800277B0)
 * VRAM 0x800277B0 | ROM 0x283B0 | size 0x28
 * asm: asm/nonmatchings/main/__osSiRelAccess.s
 */
/* SDK: libultra 2.0I, ultralib src/io/siacs.c (same code as the SDK source). */
#include "common.h"

s32 osSendMesg(void *, s32, s32);
extern s32 __osSiAccessQueue;

/* Post a zero message to the __osSiAccessQueue message queue without waiting. */
void __osSiRelAccess(void) {
    osSendMesg(&__osSiAccessQueue, 0, 0);
}
