/* @header
 * initializePiAndRdram  (originally func_800268A0)
 * VRAM 0x800268A0 | ROM 0x274A0 | size 0x248
 * asm: asm/nonmatchings/main/func_800268A0.s
 */
#include "common.h"

extern s32 D_8007DFB8;
typedef struct { u32 w[4]; } Nw2BootBlob;
extern Nw2BootBlob D_80000000;
extern u64 D_80038800;
extern s32 D_80000300, D_8000030C, D_8000031C;
extern u32 D_80038808;
extern s32 func_80026B00(void);
extern void func_80026C10(s32);
extern void func_80026C20(s32);
extern void func_80026C30(void);
extern void func_80026C80(void);
extern s32 func_800275F0(s32, s32 *);
extern s32 func_80027680(s32, s32);
extern void func_800277E0(s32, u32 *);
extern u64 func_80028860(u64, u64);
extern s32 func_8001C7E0(s32, s32);
extern s32 func_8001C660(s32, s32);
extern void func_80021F60(s32 *, s32);
extern u32 func_80025F30[];
/* Early boot bring-up: enables the PI, programs the PI bus, waits for the PI
 * status handshake, copies the four 16-byte boot blobs to 0x80000000/80/100/180,
 * invalidates the instruction and data caches, derives the RDRAM size, seeds the
 * memory-config word and programs the PI DOM1 latency/page/release registers. */
void initializePiAndRdram(void) {
    s32 piStatus;
    u32 rdramSize=0;
    D_8007DFB8=1;
    func_80026C20(func_80026B00()|0x20000000);
    func_80026C10(0x01000800);
    do {} while(func_800275F0(0x1FC007FC,&piStatus)!=0);
    do {} while(func_80027680(0x1FC007FC,piStatus|8)!=0);
    *(Nw2BootBlob *)0x80000000=*(Nw2BootBlob *)func_80025F30;
    *(Nw2BootBlob *)0x80000080=*(Nw2BootBlob *)func_80025F30;
    *(Nw2BootBlob *)0x80000100=*(Nw2BootBlob *)func_80025F30;
    *(Nw2BootBlob *)0x80000180=*(Nw2BootBlob *)func_80025F30;
    func_8001C7E0(0x80000000,0x190);
    func_8001C660(0x80000000,0x190);
    func_80026C30();func_80026C80();
    func_800277E0(4,&rdramSize);
    rdramSize &= ~0xFU;
    if(rdramSize!=0)D_80038800=rdramSize;
    D_80038800=func_80028860(D_80038800*3,4);
    if(D_8000030C==0)func_80021F60(&D_8000031C,0x40);
    if(D_80000300==0)D_80038808=0x02F5B2D2;
    else if(D_80000300==2)D_80038808=0x02E6025C;
    else D_80038808=0x02E6D354;
    *(volatile u32 *)0xA4500008=1;
    *(volatile u32 *)0xA4500010=0x3FFF;
    *(volatile u32 *)0xA4500014=0xF;
}
