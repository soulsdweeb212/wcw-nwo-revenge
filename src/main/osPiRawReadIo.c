/* @header
 * osPiRawReadIo  (originally func_800277E0)
 * VRAM 0x800277E0 | ROM 0x283E0 | size 0x94
 * asm: asm/nonmatchings/main/osPiRawReadIo.s
 */
/* SDK: libultra 2.0I, ultralib src/io/pirawread.c (same code as the SDK source). */
#include "common.h"

extern s32 __osSiAccessQueueEnabled;
extern char siAccessBuf[];
extern char __osSiAccessQueue[];
extern char D_8003B980[];
extern char D_8003B984[];
extern char D_8003B990[];
extern char D_8003B994[];
extern char D_8003B9A4[];
extern char D_8003B9A8[];
extern u32 osRomBase;

extern void osCreateMesgQueue(void *, void *, s32);
extern void osRecvMesg(void *, void *, s32);
extern void osSendMesg(void *, s32, s32);
extern void __assert(char *, char *, s32);
extern s32 __osSiDeviceBusy(void);

/* Waits for the cartridge domain bus and reads the 32-bit word at devAddr into
 * *data (asserting when data is NULL). */
s32 osPiRawReadIo(u32 devAddr, u32 *data) {
    u32 stat;

    if (data == NULL) {
        __assert(D_8003B9A4, D_8003B9A8, 0x3D);
    }
    stat = *(volatile u32 *)0xA4600010;
    while (stat & 3) {
        stat = *(volatile u32 *)0xA4600010;
    }
    *data = *(volatile u32 *)(osRomBase | devAddr | 0xA0000000);
    return 0;
}
