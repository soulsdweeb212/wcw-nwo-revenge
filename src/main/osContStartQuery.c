/* @header
 * osContStartQuery  (originally func_80021190)
 * VRAM 0x80021190 | ROM 0x21D90 | size 0x80
 * asm: asm/nonmatchings/main/osContStartQuery.s
 */
/* SDK: libultra 2.0I, ultralib src/io/contquery.c (same code as the SDK source). */
#include "common.h"

s32 osRecvMesg(s32, void *, s32);
void __osPackRequestData(s32);
s32 __osSiRawStartDma(s32, void *);
void __osSiGetAccess(void);
void __osSiRelAccess(void);
extern u8 __osContPifRam[];
extern u8 __osContLastCmd;

/* Reads the controllers with the buffer reset (__osPackRequestData) first: issues the
 * command and waits, then retrieves the response. Returns the read result. */
s32 osContStartQuery(s32 arg0) {
    s32 temp_v0;

    __osSiGetAccess();
    if (__osContLastCmd != 0) {
        __osPackRequestData(0);
        __osSiRawStartDma(1, __osContPifRam);
        osRecvMesg(arg0, 0, 1);
    }
    temp_v0 = __osSiRawStartDma(0, __osContPifRam);
    __osContLastCmd = 0;
    __osSiRelAccess();
    return temp_v0;
}
