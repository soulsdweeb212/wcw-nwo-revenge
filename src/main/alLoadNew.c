/* @header
 * alLoadNew  (originally func_8001D4E4)
 * VRAM 0x8001D4E4 | ROM 0x1E0E4 | size 0xB0
 * asm: asm/nonmatchings/main/alLoadNew.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/drvrnew.c (same code as the SDK source). */
#include "common.h"

void guMtxF2L(void *,void *);
void alFilterNew(void *,void *,void *,s32);
s32 alHeapDBAlloc(s32,s32,s32,s32,s32);
void alAdpcmPull(void);void alLoadParam(void);void alResamplePull(void);void alResampleParam(void);
/* Initializes the two-buffer audio object arg0 with its callbacks, allocates its
 * two 32-byte work buffers from arg2 and seeds its state. */
void alLoadNew(u8 *arg0,s32 (*arg1)(void *),s32 arg2) {
    alFilterNew(arg0,alAdpcmPull,alLoadParam,0);
    *(s32*)(arg0+0x14)=alHeapDBAlloc(0,0,arg2,1,32);
    *(s32*)(arg0+0x18)=alHeapDBAlloc(0,0,arg2,1,32);
    *(s32*)(arg0+0x30)=arg1(arg0+0x34);
    *(s32*)(arg0+0x3C)=0;*(s32*)(arg0+0x40)=1;*(s32*)(arg0+0x44)=0;
}
u32 osVirtualToPhysical(u32);
