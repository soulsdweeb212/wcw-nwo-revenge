/* @header
 * __osPfsGetStatus  (originally func_80024640)
 * VRAM 0x80024640 | ROM 0x25240 | size 0xF0
 * asm: asm/nonmatchings/main/__osPfsGetStatus.s
 */
/* SDK: libultra 2.0I, ultralib src/io/pfsgetstatus.c (same code as the SDK source). */
#include "common.h"

extern u8 D_800375E4;
extern u8 D_8007DFD0[];
void __osPfsRequestOneChannel(s32, s32);
s32 __osSiRawStartDma(s32, void *);
s32 osRecvMesg(void *, void *, s32);
void __osPfsGetOneChannelData(s32, void *);

/* Probe the controller pak on channel arg1: set the probe id, issue the
 * identify commands, read back the status, and classify it -- 2 for a rumble
 * pak, 1 for an unrecognised/absent pak, 4 for a pak with bit 2 set, otherwise
 * the raw command result. */
s32 __osPfsGetStatus(void *arg0, s32 arg1) {
    struct { u16 buttons; u8 status; u8 rest[3]; } status;
    s32 message;
    s32 result;
    D_800375E4 = 0xFA;
    __osPfsRequestOneChannel(arg1, 0);
    __osSiRawStartDma(1, D_8007DFD0);
    osRecvMesg(arg0, &message, 1);
    result = __osSiRawStartDma(0, D_8007DFD0);
    osRecvMesg(arg0, &message, 1);
    __osPfsGetOneChannelData(arg1, &status);
    if ((status.status & 1) && (status.status & 2)) return 2;
    if ((*(u16 *)&status.status & 0x1FF) != 0x100) return 1;
    if (status.status & 4) return 4;
    return result;
}
