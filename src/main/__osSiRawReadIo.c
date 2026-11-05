/* @header
 * __osSiRawReadIo  (originally func_800275F0)
 * VRAM 0x800275F0 | ROM 0x281F0 | size 0x90
 * asm: asm/nonmatchings/main/__osSiRawReadIo.s
 */
/* SDK: libultra 2.0I, ultralib src/io/sirawread.c (same code as the SDK source). */
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

/* Reads a 32-bit word from the cartridge domain at devAddr (asserting on
 * misalignment or NULL data), returning -1 if the bus is busy. */
s32 __osSiRawReadIo(u32 devAddr, u32 *data) {
    if (devAddr & 3) {
        __assert(D_8003B980, D_8003B984, 0x33);
    }
    if (data == NULL) {
        __assert(D_8003B980, D_8003B984, 0x34);
    }
    if (__osSiDeviceBusy() != 0) {
        return -1;
    }
    *data = *(volatile u32 *)(devAddr | 0xA0000000);
    return 0;
}
