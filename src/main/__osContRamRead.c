/* @header
 * __osContRamRead  (originally func_80022BB0)
 * VRAM 0x80022BB0 | ROM 0x237B0 | size 0x1FC
 * asm: asm/nonmatchings/main/__osContRamRead.s
 */
#include "common.h"

/* Read a 32-byte block from a Controller Pak channel: build the read packet
 * (header + address + CRC), send it with __osSiRawStartDma/osRecvMesg, then
 * verify the data CRC and copy the payload out. Retries up to 3 times. */
typedef struct {
    u8 unk00;
    u8 txsize;
    u8 rxsize;
    u8 cmd;
    u8 hi;
    u8 lo;
    u8 data[32];
    u8 datacrc;
} ContRamReadFormat;

extern u8 __osPfsPifRam[];
extern s32 D_8007E00C;
extern s32 __osPfsLastChannel;

s32 osRecvMesg(void *, void *, s32);
void bcopy(void *, void *, s32);
s32 __osSiRawStartDma(s32, void *);
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 __osPfsGetStatus(void *, s32);

s32 __osContRamRead(void *mq, s32 channel, u16 addr, u8 *buffer) {
    s32 status;
    s32 i;
    u8 *pkt = __osPfsPifRam;
    ContRamReadFormat *fmt;
    s32 retryCount = 2;

    __osSiGetAccess();
    do {
        if (__osContLastCmd != 2 || __osPfsLastChannel != channel) {
            __osContLastCmd = 2;
            __osPfsLastChannel = channel;
            for (i = 0; i < channel; i++) {
                *pkt++ = 0;
            }
            D_8007E00C = 1;
            fmt = (ContRamReadFormat *)pkt;
            fmt->unk00 = 0xFF;
            fmt->txsize = 3;
            fmt->rxsize = 0x21;
            fmt->cmd = 2;
            fmt->datacrc = 0xFF;
            pkt[sizeof(ContRamReadFormat)] = 0xFE;
        } else {
            pkt += channel;
        }
        fmt = (ContRamReadFormat *)pkt;
        fmt->hi = addr >> 3;
        fmt->lo = __osContAddressCrc(addr) | (addr << 5);
        __osSiRawStartDma(1, __osPfsPifRam);
        osRecvMesg(mq, NULL, 1);
        __osSiRawStartDma(0, __osPfsPifRam);
        osRecvMesg(mq, NULL, 1);
        status = (fmt->rxsize & 0xC0) >> 4;
        if (status == 0) {
            if ((u8)__osContDataCrc(pkt + 6) != fmt->datacrc) {
                status = __osPfsGetStatus(mq, channel);
                if (status != 0) break;
                status = 4;
            } else {
                bcopy(pkt + 6, buffer, 32);
            }
        } else {
            status = 1;
        }
        if (status != 4) break;
    } while (0 <= retryCount--);
    __osSiRelAccess();
    return status;
}
