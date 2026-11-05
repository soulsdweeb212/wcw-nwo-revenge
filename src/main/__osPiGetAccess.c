/* @header
 * __osPiGetAccess  (originally func_80027F54)
 * VRAM 0x80027F54 | ROM 0x28B54 | size 0x6C
 * asm: asm/nonmatchings/main/__osPiGetAccess.s
 */
/* SDK: libultra 2.0I, ultralib src/io/piacs.c (same code as the SDK source). */
#include "common.h"

extern s32 D_800389A0;
extern u8 D_80064AC0[];
extern u8 D_80073E98[];
extern u8 D_80070A98;

extern s32 D_80037248;
extern void *D_80037250;

s32 osCreateMesgQueue(void *, void *, s32);
s32 osRecvMesg(void *, void *, s32);
s32 osSendMesg(void *, s32, s32);
s32 __osDisableInt(void);
void __osEnqueueAndYield(s32 *, s32);
void __osRestoreInt(s32);

/* Lazily initializes the Controller Pak message queue and then blocks for one
 * message into sp10. */
void __osPiGetAccess(void) {
    s32 sp10;

    if (D_800389A0 == 0) {
        D_800389A0 = 1;
        osCreateMesgQueue(D_80064AC0 + 0xF3D8, D_80064AC0, 1);
        osSendMesg(D_80073E98, 0, 0);
    }
    osRecvMesg((u8 *)&D_80070A98 + 0x3400, &sp10, 1);
}
