/* @header
 * __osPiCreateAccessQueue  (originally func_80027F00)
 * VRAM 0x80027F00 | ROM 0x28B00 | size 0x54
 * asm: asm/nonmatchings/main/__osPiCreateAccessQueue.s
 */
/* SDK: libultra 2.0I, ultralib src/io/piacs.c (same code as the SDK source). */
#include "common.h"

s32 osCreateMesgQueue(s32 *, s32 *, s32);
s32 osSendMesg(s32 *, s32, s32);
extern s32 D_800389A0;
extern s32 D_80064AC0;
extern s32 D_80073E98;

/* Initialize the message queue at D_80073E98 from D_80064AC0, mark it active, and
 * send a zero message. */
void __osPiCreateAccessQueue(void) {
    D_800389A0 = 1;
    osCreateMesgQueue(&D_80073E98, &D_80064AC0, 1);
    osSendMesg(&D_80073E98, 0, 0);
}
