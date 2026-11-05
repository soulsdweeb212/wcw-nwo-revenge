/* @header
 * osInitialize  (originally func_800268A0)
 * VRAM 0x800268A0 | ROM 0x274A0 | size 0x248
 * asm: asm/nonmatchings/main/osInitialize.s
 */
/* SDK: libultra 2.0I, ultralib src/os/initialize.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

extern s32 __osFinalrom;
typedef struct { u32 w[4]; } Nw2BootBlob;
extern Nw2BootBlob D_80000000;
extern u64 osClockRate;
extern s32 osTvType, osResetType, osAppNMIBuffer;
extern u32 osViClock;
extern s32 __osGetSR(void);
extern void __osSetFpcCsr(s32);
extern void __osSetSR(s32);
extern void osUnmapTLBAll(void);
extern void osMapTLBRdb(void);
extern s32 __osSiRawReadIo(s32, s32 *);
extern s32 __osSiRawWriteIo(s32, s32);
extern void osPiRawReadIo(s32, u32 *);
extern u64 __udivdi3(u64, u64);
extern s32 osWritebackDCache(s32, s32);
extern s32 osInvalICache(s32, s32);
extern void bzero(s32 *, s32);
extern u32 __osExceptionPreamble[];
/* Early boot bring-up: enables the PI, programs the PI bus, waits for the PI
 * status handshake, copies the four 16-byte boot blobs to 0x80000000/80/100/180,
 * invalidates the instruction and data caches, derives the RDRAM size, seeds the
 * memory-config word and programs the PI DOM1 latency/page/release registers. */
void osInitialize(void) {
    s32 piStatus;
    u32 rdramSize=0;
    __osFinalrom=1;
    __osSetSR(__osGetSR()|0x20000000);
    __osSetFpcCsr(0x01000800);
    do {} while(__osSiRawReadIo(0x1FC007FC,&piStatus)!=0);
    do {} while(__osSiRawWriteIo(0x1FC007FC,piStatus|8)!=0);
    *(Nw2BootBlob *)0x80000000=*(Nw2BootBlob *)__osExceptionPreamble;
    *(Nw2BootBlob *)0x80000080=*(Nw2BootBlob *)__osExceptionPreamble;
    *(Nw2BootBlob *)0x80000100=*(Nw2BootBlob *)__osExceptionPreamble;
    *(Nw2BootBlob *)0x80000180=*(Nw2BootBlob *)__osExceptionPreamble;
    osWritebackDCache(0x80000000,0x190);
    osInvalICache(0x80000000,0x190);
    osUnmapTLBAll();osMapTLBRdb();
    osPiRawReadIo(4,&rdramSize);
    rdramSize &= ~0xFU;
    if(rdramSize!=0)osClockRate=rdramSize;
    osClockRate=__udivdi3(osClockRate*3,4);
    if(osResetType==0)bzero(&osAppNMIBuffer,0x40);
    if(osTvType==0)osViClock=0x02F5B2D2;
    else if(osTvType==2)osViClock=0x02E6025C;
    else osViClock=0x02E6D354;
    *(volatile u32 *)0xA4500008=1;
    *(volatile u32 *)0xA4500010=0x3FFF;
    *(volatile u32 *)0xA4500014=0xF;
}
