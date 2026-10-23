#include "common.h"

/* Read a 32-byte block from a Controller Pak channel: build the read packet
 * (header + address + CRC), send it with func_80025810/func_8001C990, then
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

extern u8 D_8007DFD0[];
extern s32 D_8007E00C;
extern s32 D_800375F0;

s32 func_8001C990(void *, void *, s32);
void func_80021C40(void *, void *, s32);
s32 func_80025810(s32, void *);
void func_80027744(void);
void func_800277B0(void);
s32 func_80024640(void *, s32);

s32 __osContRamRead(void *mq, s32 channel, u16 addr, u8 *buffer) {
    s32 status;
    s32 i;
    u8 *pkt = D_8007DFD0;
    ContRamReadFormat *fmt;
    s32 retryCount = 2;

    func_80027744();
    do {
        if (D_8007BD30 != 2 || D_800375F0 != channel) {
            D_8007BD30 = 2;
            D_800375F0 = channel;
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
        fmt->lo = calculateControllerPakAddressCrc(addr) | (addr << 5);
        func_80025810(1, D_8007DFD0);
        func_8001C990(mq, NULL, 1);
        func_80025810(0, D_8007DFD0);
        func_8001C990(mq, NULL, 1);
        status = (fmt->rxsize & 0xC0) >> 4;
        if (status == 0) {
            if ((u8)calculateControllerPakDataCrc(pkt + 6) != fmt->datacrc) {
                status = func_80024640(mq, channel);
                if (status != 0) break;
                status = 4;
            } else {
                func_80021C40(pkt + 6, buffer, 32);
            }
        } else {
            status = 1;
        }
        if (status != 4) break;
    } while (0 <= retryCount--);
    func_800277B0();
    return status;
}
