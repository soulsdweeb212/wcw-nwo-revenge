/* @header
 * __osSiRawWriteIo  (originally func_80027680)
 * VRAM 0x80027680 | ROM 0x28280 | size 0x6C
 * asm: asm/nonmatchings/main/__osSiRawWriteIo.s
 */
/* SDK: libultra 2.0I, ultralib src/io/sirawwrite.c (same code as the SDK source). */
#include "common.h"

extern s32 D_800388A0;
extern char D_80064AB0[];
extern char D_8007E210[];
extern char D_8003B980[];
extern char D_8003B984[];
extern char D_8003B990[];
extern char D_8003B994[];
extern char D_8003B9A4[];
extern char D_8003B9A8[];
extern u32 D_80000308;

extern void osCreateMesgQueue(void *, void *, s32);
extern void osRecvMesg(void *, void *, s32);
extern void osSendMesg(void *, s32, s32);
extern void __assert(char *, char *, s32);
extern s32 __osSiDeviceBusy(void);

/* Writes a 32-bit word to the cartridge domain at devAddr (asserting on
 * misalignment), returning -1 if the bus is busy. */
s32 __osSiRawWriteIo(u32 devAddr, u32 data) {
    if (devAddr & 3) {
        __assert(D_8003B990, D_8003B994, 0x34);
    }
    if (__osSiDeviceBusy() != 0) {
        return -1;
    }
    *(volatile u32 *)(devAddr | 0xA0000000) = data;
    return 0;
}
