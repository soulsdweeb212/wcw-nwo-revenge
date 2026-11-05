/* @header
 * __osContRamWrite  (originally func_80022DB0)
 * VRAM 0x80022DB0 | ROM 0x239B0 | size 0x21C
 * asm: asm/nonmatchings/main/__osContRamWrite.s
 */
#include "common.h"

typedef struct {
    u8 dummy;
    u8 txsize;
    u8 rxsize;
    u8 cmd;
    u8 addrh;
    u8 addrl;
    u8 data[32];
    u8 datacrc;
} __OSContRamReadFormat;

typedef struct {
    u32 ramarray[15];
    u32 pifstatus;
} __OSPifRam;

extern __OSPifRam __osPfsPifRam;
extern u8 __osContLastCmd;
extern s32 __osPfsLastChannel;

#define READFORMAT(ptr) ((__OSContRamReadFormat*)(ptr))
#define CHNL_ERR(format) (((format).rxsize & 0xC0) >> 4)

#define CONT_CMD_REQUEST_STATUS 0
#define CONT_CMD_WRITE_PAK 3
#define CONT_CMD_WRITE_PAK_TX 35
#define CONT_CMD_WRITE_PAK_RX 1
#define CONT_CMD_EXE 1
#define CONT_CMD_NOP 0xff
#define CONT_CMD_END 0xfe
#define BLOCKSIZE 32
#define TRUE 1
#define FALSE 0
#define PFS_LABEL_AREA 7
#define PFS_ERR_CONTRFAIL 4
#define PFS_ERR_NOPACK 1
#define OS_WRITE 1
#define OS_READ 0
#define OS_MESG_BLOCK 1

void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 __osSiRawStartDma(s32, void *);
s32 osRecvMesg(void *, void *, s32);
void bcopy(void *, void *, s32);
s32 __osContAddressCrc(u16);
s32 __osContDataCrc(u8 *);
s32 __osPfsGetStatus(void *, int);

/* SDK: writes one 32-byte block of Controller Pak data for `channel`. Builds
 * the PIF packet (block header once per channel), writes the address and its
 * CRC, sends the write then a read-back, verifies the data CRC and retries on
 * controller failure. Returns 0 on success or a PFS_ERR_* code. The label area
 * (blocks 1..6) is only writable when `force` is set. */
s32 __osContRamWrite(void *mq, int channel, u16 address, u8 *buffer, int force) {
    s32 err = 0;
    s32 ch;
    u8 *pif = (u8 *)__osPfsPifRam.ramarray;
    s32 tries = 2;
    u8 dataCrc;

    if ((force != TRUE) && (address < PFS_LABEL_AREA) && (address != 0)) {
        return 0;
    }

    __osSiGetAccess();

    do {
        if (__osContLastCmd != CONT_CMD_WRITE_PAK || (u32)__osPfsLastChannel != channel) {
            __osContLastCmd = CONT_CMD_WRITE_PAK;
            __osPfsLastChannel = channel;

            for (ch = 0; ch < channel; ch++) {
                *pif++ = CONT_CMD_REQUEST_STATUS;
            }

            __osPfsPifRam.pifstatus = CONT_CMD_EXE;

            READFORMAT(pif)->dummy = CONT_CMD_NOP;
            READFORMAT(pif)->txsize = CONT_CMD_WRITE_PAK_TX;
            READFORMAT(pif)->rxsize = CONT_CMD_WRITE_PAK_RX;
            READFORMAT(pif)->cmd = CONT_CMD_WRITE_PAK;
            READFORMAT(pif)->datacrc = 0xFF;

            pif[sizeof(__OSContRamReadFormat)] = CONT_CMD_END;
        } else {
            pif += channel;
        }

        READFORMAT(pif)->addrh = address >> 3;
        READFORMAT(pif)->addrl = (__osContAddressCrc(address) | (address << 5));

        bcopy(buffer, READFORMAT(pif)->data, BLOCKSIZE);

        err = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        dataCrc = __osContDataCrc(buffer);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        err = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        err = CHNL_ERR(*READFORMAT(pif));

        if (!err) {
            if (dataCrc != READFORMAT(pif)->datacrc) {
                if ((err = __osPfsGetStatus(mq, channel))) {
                    break;
                } else {
                    err = PFS_ERR_CONTRFAIL;
                }
            }
        } else {
            err = PFS_ERR_NOPACK;
        }
    } while ((err == PFS_ERR_CONTRFAIL) && (tries-- >= 0));

    __osSiRelAccess();

    return err;
}
