/* @header
 * __osPiRelAccess  (originally func_80027FC0)
 * VRAM 0x80027FC0 | ROM 0x28BC0 | size 0x28
 * asm: asm/nonmatchings/main/__osPiRelAccess.s
 */
/* SDK: libultra 2.0I, ultralib src/io/piacs.c (same code as the SDK source). */
#include "common.h"

s32 osSendMesg(s32 *, s32, s32);
extern s32 __osPiAccessQueue;

/* Send a zero message to the queue at __osPiAccessQueue. */
void __osPiRelAccess(void) {
    osSendMesg(&__osPiAccessQueue, 0, 0);
}
