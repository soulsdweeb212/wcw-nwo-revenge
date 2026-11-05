/* @header
 * alResampleNew  (originally func_8001D594)
 * VRAM 0x8001D594 | ROM 0x1E194 | size 0x8C
 * asm: asm/nonmatchings/main/alResampleNew.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/drvrnew.c (same code as the SDK source). */
#include "common.h"

void guMtxF2L(void *,void *);
void alFilterNew(void *,void *,void *,s32);
s32 alHeapDBAlloc(s32,s32,s32,s32,s32);
void alAdpcmPull(void);void alLoadParam(void);void alResamplePull(void);void alResampleParam(void);
/* Initializes the single-buffer audio object arg0 with its callbacks and one
 * 32-byte work buffer from arg1, and resets its state fields. */
void alResampleNew(u8 *arg0,s32 arg1) {
    alFilterNew(arg0,alResamplePull,alResampleParam,1);
    *(s32*)(arg0+0x14)=alHeapDBAlloc(0,0,arg1,1,32);
    *(s32*)(arg0+0x20)=0;*(s32*)(arg0+0x24)=1;*(s32*)(arg0+0x30)=0;
    *(s32*)(arg0+0x1C)=0;*(s32*)(arg0+0x28)=0;*(s32*)(arg0+0x2C)=0;
    *(f32*)(arg0+0x18)=1.0f;
}
u32 osVirtualToPhysical(u32);
