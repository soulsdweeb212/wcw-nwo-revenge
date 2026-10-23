#include "common.h"

typedef struct {s16 id,state;u8 *buffer,*source,*destination;s32 remaining;u8 pad14[0x44];u8 queue[24];u16 type;u8 priority,status;void *returnQueue;u8 *dram,*cart;s32 size;u8 tail[0x78];} StreamSlot;
extern StreamSlot D_800706AC[];
extern u8 *D_800485A0[];extern s32 D_8004859C;
void lookupResourceDescriptor(void *,u16);void func_8001C5B0(void *,s32);s32 func_800219B0(s32,void *,s32);s32 func_8001C990(void *,void *,s32);
/* Begin streaming resource `resId` into slot `slot`: look up its descriptor,
 * point the slot at the payload (descriptor + 4 bytes), prime the first chunk,
 * hook up the ring queue and reset the slot state, then wait for the DMA engine
 * to report idle before returning. */
void initializeResourceStream(s16 slot,s16 resId){s32 info[4];s32 n;
lookupResourceDescriptor(info,(u16)resId);D_800706AC[slot].source=(u8*)info[0]+4;D_800706AC[slot].destination=D_800485A0[slot];D_800706AC[slot].remaining=info[2]-4;n=256;
func_8001C5B0(D_800706AC[slot].destination,D_800706AC[slot].remaining);if(D_800706AC[slot].remaining<256)n=D_800706AC[slot].remaining;
D_800706AC[slot].returnQueue=D_800706AC[slot].queue;D_800706AC[slot].priority=0;D_800706AC[slot].size=n;D_800706AC[slot].cart=D_800706AC[slot].source;D_800706AC[slot].dram=D_800706AC[slot].destination;
do{}while(func_800219B0(D_8004859C,&D_800706AC[slot].type,0));
D_800706AC[slot].id=resId;D_800706AC[slot].source+=n;D_800706AC[slot].destination+=n;D_800706AC[slot].remaining-=n;D_800706AC[slot].buffer=D_800485A0[slot];D_800706AC[slot].state=0;func_8001C990(D_800706AC[slot].queue,0,1);
}
