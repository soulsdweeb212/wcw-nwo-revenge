/* @header
 * osMotorInit  (originally func_800233E4)
 * VRAM 0x800233E4 | ROM 0x23FE4 | size 0x248
 * asm: asm/nonmatchings/main/osMotorInit.s
 */
/* SDK: libultra 2.0I, ultralib src/io/motor.c (same code as the SDK source). */
#include "common.h"

extern u8 __MotorDataBuf[];
s32 __osPfsSelectBank(u8 *, s32);
s32 __osContRamRead(s32, s32, s32, void *);
s32 __osContAddressCrc(u16);

typedef struct { u8 b[0x27]; } Nw2Cmd39;

/* Reads and then rewrites Controller Pak bank `bank` for pak `pfs`:
 * builds the bank-select command in `cmd`, selects bank 0xFE then 0x80,
 * performs the 0x400-byte transfer into `resp`, and on success writes the
 * zero-filled sector at __MotorDataBuf + bank*0x40 using a 0x23
 * write command.  Returns 0 on success, or 2/4/0xB on the various errors. */
s32 osMotorInit(s32 pfs, u8 *cmd, s32 bank) {
    u8 resp[0x20];
    Nw2Cmd39 writeCmd;
    u8 *dst;
    s32 r;
    s32 i;

    *(s32 *)(cmd + 4) = pfs;
    *(s32 *)(cmd + 8) = bank;
    cmd[0x65] = 0xFF;
    *(s32 *)cmd = 0;

    r = __osPfsSelectBank(cmd, 0xFE);
    if (r == 2) {
        r = __osPfsSelectBank(cmd, 0x80);
    }
    if (r != 0) {
        return r;
    }
    r = __osContRamRead(pfs, bank, 0x400, resp);
    if (r == 2) {
        r = 4;
    }
    if (r != 0) {
        return r;
    }
    if (resp[0x1F] == 0xFE) {
        return 0xB;
    }
    r = __osPfsSelectBank(cmd, 0x80);
    if (r == 2) {
        r = 4;
    }
    if (r != 0) {
        return r;
    }
    r = __osContRamRead(pfs, bank, 0x400, resp);
    if (r == 2) {
        r = 4;
    }
    if (r != 0) {
        return r;
    }
    if (resp[0x1F] != 0x80) {
        return 0xB;
    }
    if (!(*(u32 *)cmd & 8)) {
        dst = __MotorDataBuf + (bank << 6);
        writeCmd.b[0] = 0xFF;
        writeCmd.b[1] = 0x23;
        writeCmd.b[2] = 1;
        writeCmd.b[3] = 3;
        writeCmd.b[4] = 0xC0;
        writeCmd.b[5] = __osContAddressCrc(0x600);
        if (bank != 0) {
            for (i = 0; i < bank; i++) {
                *dst++ = 0;
            }
        }
        *(Nw2Cmd39 *)dst = writeCmd;
        dst[0x27] = 0xFE;
    }
    *(u32 *)cmd = 8;
    return 0;
}
