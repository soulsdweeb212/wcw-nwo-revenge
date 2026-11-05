/* @header
 * osContStartReadData  (originally func_80022FD0)
 * VRAM 0x80022FD0 | ROM 0x23BD0 | size 0x88
 * asm: asm/nonmatchings/main/osContStartReadData.s
 */
/* SDK: libultra 2.0I, ultralib src/io/contreaddata.c (same code as the SDK source). */
#include "common.h"

s32 osRecvMesg(s32, void *, s32);
void __osPackReadData(void);
s32 __osSiRawStartDma(s32, void *);
void __osSiGetAccess(void);
void __osSiRelAccess(void);
extern u8 __osContPifRam[];
extern u8 __osContLastCmd;

/* Reads the controllers: if the previous packet is not already buffered it
 * issues the read command and waits on the queue, then retrieves the response.
 * Returns the read result. */
s32 osContStartReadData(s32 arg0) {
    s32 temp_v0;

    __osSiGetAccess();
    if (__osContLastCmd != 1) {
        __osPackReadData();
        __osSiRawStartDma(1, __osContPifRam);
        osRecvMesg(arg0, 0, 1);
    }
    temp_v0 = __osSiRawStartDma(0, __osContPifRam);
    __osContLastCmd = 1;
    __osSiRelAccess();
    return temp_v0;
}
