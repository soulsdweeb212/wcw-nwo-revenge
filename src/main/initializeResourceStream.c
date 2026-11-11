/* @header
 * initializeResourceStream  (originally func_80009784)
 * VRAM 0x80009784 | ROM 0xA384 | size 0x20C
 * asm: asm/nonmatchings/main/initializeResourceStream.s
 */
#include "common.h"

typedef struct {s16 id,state;u8 *buffer,*source,*destination;s32 remaining;u8 pad14[0x44];u8 queue[24];u16 type;u8 priority,status;void *returnQueue;u8 *dram,*cart;s32 size;u8 tail[0x78];} StreamSlot;
#ifndef TARGET_PC /* on PC this label of the stream record D_800706A8 does not exist: it is read by field name */
extern StreamSlot D_800706AC[];
#endif
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
#ifdef TARGET_PC
/* PC: the stream record is Nw2AnimStream (common.h), read by field name: source is a RomAddr (the resource's ROM
 * address from info[0], a RomAddr in port.h's ResDesc), cursor and destination are host pointers, and the read is the
 * PortIoMesg request io (port.h). The N64 code reaches the same fields through its view StreamSlot at the label
 * D_800706AC, 4 bytes into the record: buffer is cursor, state firstFrame, type the request. */
void initializeResourceStream(s16 slot, s16 resId)
{
    Nw2AnimStream *s = &D_800706A8[slot];
    s32 info[4];
    s32 n;

    lookupResourceDescriptor(info, (u16)resId);
    s->source = (RomAddr)info[0] + 4;
    s->destination = D_800485A0[slot];
    s->remaining = info[2] - 4;
    n = 256;
    osInvalDCache(s->destination, s->remaining);
    if (s->remaining < 256) {
        n = s->remaining;
    }
    s->io.retQueue = s->queue;
    s->io.pri = 0;
    s->io.size = n;
    s->io.devAddr = s->source;
    s->io.dramAddr = s->destination;
    do {
    } while (osEPiStartDma(D_8004859C, &s->io, 0));
    s->id = resId;
    s->source += n;
    s->destination += n;
    s->remaining -= n;
    s->cursor = D_800485A0[slot];
    s->firstFrame = 0;
    osRecvMesg(s->queue, 0, 1);
}
#else
void initializeResourceStream(s16 slot,s16 resId){s32 info[4];s32 n;
    lookupResourceDescriptor(info,(u16)resId);D_800706AC[slot].source=(u8*)info[0]+4;D_800706AC[slot].destination=D_800485A0[slot];D_800706AC[slot].remaining=info[2]-4;n=256;
    osInvalDCache(D_800706AC[slot].destination,D_800706AC[slot].remaining);if(D_800706AC[slot].remaining<256)n=D_800706AC[slot].remaining;
    D_800706AC[slot].returnQueue=D_800706AC[slot].queue;D_800706AC[slot].priority=0;D_800706AC[slot].size=n;D_800706AC[slot].cart=D_800706AC[slot].source;D_800706AC[slot].dram=D_800706AC[slot].destination;
    do{}while(osEPiStartDma(D_8004859C,&D_800706AC[slot].type,0));
    D_800706AC[slot].id=resId;D_800706AC[slot].source+=n;D_800706AC[slot].destination+=n;D_800706AC[slot].remaining-=n;D_800706AC[slot].buffer=D_800485A0[slot];D_800706AC[slot].state=0;osRecvMesg(D_800706AC[slot].queue,0,1);
}
#endif
