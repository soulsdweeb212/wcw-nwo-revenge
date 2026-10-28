#include "common.h"

/* CRC over the 11-bit Controller Pak block address. */
s32 calculateControllerPakAddressCrc(u16 address){
    u32 crc = 0, mask;
    for (mask = 0x400; mask; mask >>= 1) {
        crc <<= 1;
        if (address & mask) {
            if (crc & 0x20) crc ^= 0x14;
            else crc++;
        } else if (crc & 0x20) {
            crc ^= 0x15;
        }
    }
    for (mask = 5; mask; mask--) {
        crc <<= 1;
        if (crc & 0x20) crc ^= 0x15;
    }
    return crc & 31;
}

typedef struct Dispatch Dispatch;
struct Dispatch { s32 f0, f4; s32 (*callback)(void *, s32, s32); };
typedef struct {
    Dispatch *child;
    s32 pad[5];
    s32 f18, f1c, f20, f24, f28, f2c, f30;
} Parent;
