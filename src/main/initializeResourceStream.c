/* @header
 * initializeResourceStream  (originally func_80009784)
 * VRAM 0x80009784 | ROM 0xA384 | size 0x20C
 * asm: asm/nonmatchings/main/initializeResourceStream.s
 */
#include "common.h"

typedef struct {s16 id,state;u8 *buffer,*source,*destination;s32 remaining;u8 pad14[0x44];u8 queue[24];u16 type;u8 priority,status;void *returnQueue;u8 *dram,*cart;s32 size;u8 tail[0x78];} StreamSlot;
extern StreamSlot D_800706AC[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_800485A0 and D_8004859C */
extern u8 *D_800485A0[];extern s32 D_8004859C;
#endif
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(void *,u16);
#endif
#ifdef TARGET_PC
/* PC: osEPiStartDma's first argument is the PI handle, a pointer (D_8004859C), which an s32 would cut in half. */
void osInvalDCache(void *,s32);s32 osEPiStartDma(void *,void *,s32);s32 osRecvMesg(void *,void *,s32);
#else
void osInvalDCache(void *,s32);s32 osEPiStartDma(s32,void *,s32);s32 osRecvMesg(void *,void *,s32);
#endif
/* Begin streaming resource `resId` into slot `slot`: look up its descriptor,
 * point the slot at the payload (descriptor + 4 bytes), prime the first chunk,
 * hook up the ring queue and reset the slot state, then wait for the DMA engine
 * to report idle before returning. */
void initializeResourceStream(s16 slot,s16 resId){s32 info[4];s32 n;
#ifdef TARGET_PC
    /* PC: info[0] is the resource's ROM address (a RomAddr in port.h's ResDesc), the cartridge address of the stream's
     * DMA; it is widened to the pointer's width without changing its value. */
    lookupResourceDescriptor(info,(u16)resId);D_800706AC[slot].source=(u8*)((uptr)(u32)info[0]+4);D_800706AC[slot].destination=D_800485A0[slot];D_800706AC[slot].remaining=info[2]-4;n=256;
#else
    lookupResourceDescriptor(info,(u16)resId);D_800706AC[slot].source=(u8*)info[0]+4;D_800706AC[slot].destination=D_800485A0[slot];D_800706AC[slot].remaining=info[2]-4;n=256;
#endif
    osInvalDCache(D_800706AC[slot].destination,D_800706AC[slot].remaining);if(D_800706AC[slot].remaining<256)n=D_800706AC[slot].remaining;
    D_800706AC[slot].returnQueue=D_800706AC[slot].queue;D_800706AC[slot].priority=0;D_800706AC[slot].size=n;D_800706AC[slot].cart=D_800706AC[slot].source;D_800706AC[slot].dram=D_800706AC[slot].destination;
    do{}while(osEPiStartDma(D_8004859C,&D_800706AC[slot].type,0));
    D_800706AC[slot].id=resId;D_800706AC[slot].source+=n;D_800706AC[slot].destination+=n;D_800706AC[slot].remaining-=n;D_800706AC[slot].buffer=D_800485A0[slot];D_800706AC[slot].state=0;osRecvMesg(D_800706AC[slot].queue,0,1);
}
