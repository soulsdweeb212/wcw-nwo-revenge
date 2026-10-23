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

extern __OSPifRam D_8007DFD0;
extern u8 D_8007BD30;
extern s32 D_800375F0;

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

void func_80027744(void);
void func_800277B0(void);
s32 func_80025810(s32, void *);
s32 func_8001C990(void *, void *, s32);
void func_80021C40(void *, void *, s32);
s32 calculateControllerPakAddressCrc(u16);
s32 calculateControllerPakDataCrc(u8 *);
s32 func_80024640(void *, int);

/* SDK: writes one 32-byte block of Controller Pak data for `channel`. Builds
 * the PIF packet (block header once per channel), writes the address and its
 * CRC, sends the write then a read-back, verifies the data CRC and retries on
 * controller failure. Returns 0 on success or a PFS_ERR_* code. The label area
 * (blocks 1..6) is only writable when `force` is set. */
s32 __osContRamWrite(void *mq, int channel, u16 address, u8 *buffer, int force) {
    s32 err = 0;
    s32 ch;
    u8 *pif = (u8 *)D_8007DFD0.ramarray;
    s32 tries = 2;
    u8 dataCrc;

    if ((force != TRUE) && (address < PFS_LABEL_AREA) && (address != 0)) {
        return 0;
    }

    func_80027744();

    do {
        if (D_8007BD30 != CONT_CMD_WRITE_PAK || (u32)D_800375F0 != channel) {
            D_8007BD30 = CONT_CMD_WRITE_PAK;
            D_800375F0 = channel;

            for (ch = 0; ch < channel; ch++) {
                *pif++ = CONT_CMD_REQUEST_STATUS;
            }

            D_8007DFD0.pifstatus = CONT_CMD_EXE;

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
        READFORMAT(pif)->addrl = (calculateControllerPakAddressCrc(address) | (address << 5));

        func_80021C40(buffer, READFORMAT(pif)->data, BLOCKSIZE);

        err = func_80025810(OS_WRITE, &D_8007DFD0);
        dataCrc = calculateControllerPakDataCrc(buffer);
        func_8001C990(mq, NULL, OS_MESG_BLOCK);

        err = func_80025810(OS_READ, &D_8007DFD0);
        func_8001C990(mq, NULL, OS_MESG_BLOCK);

        err = CHNL_ERR(*READFORMAT(pif));

        if (!err) {
            if (dataCrc != READFORMAT(pif)->datacrc) {
                if ((err = func_80024640(mq, channel))) {
                    break;
                } else {
                    err = PFS_ERR_CONTRFAIL;
                }
            }
        } else {
            err = PFS_ERR_NOPACK;
        }
    } while ((err == PFS_ERR_CONTRFAIL) && (tries-- >= 0));

    func_800277B0();

    return err;
}
