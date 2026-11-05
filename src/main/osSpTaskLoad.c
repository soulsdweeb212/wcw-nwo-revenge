/* @header
 * osSpTaskLoad  (originally func_80020B40)
 * VRAM 0x80020B40 | ROM 0x21740 | size 0x20C
 * asm: asm/nonmatchings/main/osSpTaskLoad.s
 */
/* SDK: libultra 2.0I, ultralib src/io/sptask.c (same code as the SDK source). */
#include "common.h"

typedef struct {u32 type,flags;void *boot;u32 bootSize;void *ucode;u32 ucodeSize;void *data;u32 dataSize;void *stack;u32 stackSize;void *output;void *outputSize;void *input;u32 inputSize;u32 *yield;u32 yieldSize;} Task20B;
extern Task20B D_80062580;
void bcopy(void *,void *,s32);void *osVirtualToPhysical(void *);void osWritebackDCache(void *,s32);void __osSpSetStatus(s32);s32 __osSpSetPc(s32);s32 __osSpRawStartDma(s32,s32,void *,s32);s32 __osSpDeviceBusy(void);
/* Build and submit an RSP task: copy the caller's task into the shared DMA
 * buffer D_80062580, virtual-to-physical-translate every data pointer, fold a
 * yield task's data/ucode into it, then run the SP DMA boot sequence (halt,
 * wait for status, load the task header, then load the boot image). */
void osSpTaskLoad(Task20B *task){Task20B *dmaTask=&D_80062580;
    bcopy(task,dmaTask,64);
    if(dmaTask->ucode)dmaTask->ucode=osVirtualToPhysical(dmaTask->ucode);if(dmaTask->data)dmaTask->data=osVirtualToPhysical(dmaTask->data);if(dmaTask->stack)dmaTask->stack=osVirtualToPhysical(dmaTask->stack);if(dmaTask->output)dmaTask->output=osVirtualToPhysical(dmaTask->output);if(dmaTask->outputSize)dmaTask->outputSize=osVirtualToPhysical(dmaTask->outputSize);if(dmaTask->input)dmaTask->input=osVirtualToPhysical(dmaTask->input);if(dmaTask->yield)dmaTask->yield=osVirtualToPhysical(dmaTask->yield);
    if(dmaTask->flags&1){dmaTask->data=dmaTask->yield;dmaTask->dataSize=dmaTask->yieldSize;task->flags&=~1;if(dmaTask->flags&4)dmaTask->ucode=*(void**)((u32)task->yield+0xBFC|0xA0000000);}
    osWritebackDCache(dmaTask,64);__osSpSetStatus(0x2B00);do{}while(__osSpSetPc(0x04001000)==-1);do{}while(__osSpRawStartDma(1,0x04000FC0,dmaTask,64)==-1);do{}while(__osSpDeviceBusy());do{}while(__osSpRawStartDma(1,0x04001000,dmaTask->boot,dmaTask->bootSize)==-1);
}
