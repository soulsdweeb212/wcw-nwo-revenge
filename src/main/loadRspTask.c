#include "common.h"

typedef struct {u32 type,flags;void *boot;u32 bootSize;void *ucode;u32 ucodeSize;void *data;u32 dataSize;void *stack;u32 stackSize;void *output;void *outputSize;void *input;u32 inputSize;u32 *yield;u32 yieldSize;} Task20B;
extern Task20B D_80062580;
void func_80021C40(void *,void *,s32);void *func_8001CE80(void *);void func_8001C7E0(void *,s32);void func_80027390(s32);s32 func_800273A0(s32);s32 func_800273D0(s32,s32,void *,s32);s32 func_80027360(void);
/* Build and submit an RSP task: copy the caller's task into the shared DMA
 * buffer D_80062580, virtual-to-physical-translate every data pointer, fold a
 * yield task's data/ucode into it, then run the SP DMA boot sequence (halt,
 * wait for status, load the task header, then load the boot image). */
void loadRspTask(Task20B *task){Task20B *dmaTask=&D_80062580;
func_80021C40(task,dmaTask,64);
if(dmaTask->ucode)dmaTask->ucode=func_8001CE80(dmaTask->ucode);if(dmaTask->data)dmaTask->data=func_8001CE80(dmaTask->data);if(dmaTask->stack)dmaTask->stack=func_8001CE80(dmaTask->stack);if(dmaTask->output)dmaTask->output=func_8001CE80(dmaTask->output);if(dmaTask->outputSize)dmaTask->outputSize=func_8001CE80(dmaTask->outputSize);if(dmaTask->input)dmaTask->input=func_8001CE80(dmaTask->input);if(dmaTask->yield)dmaTask->yield=func_8001CE80(dmaTask->yield);
if(dmaTask->flags&1){dmaTask->data=dmaTask->yield;dmaTask->dataSize=dmaTask->yieldSize;task->flags&=~1;if(dmaTask->flags&4)dmaTask->ucode=*(void**)((u32)task->yield+0xBFC|0xA0000000);}
func_8001C7E0(dmaTask,64);func_80027390(0x2B00);do{}while(func_800273A0(0x04001000)==-1);do{}while(func_800273D0(1,0x04000FC0,dmaTask,64)==-1);do{}while(func_80027360());do{}while(func_800273D0(1,0x04001000,dmaTask->boot,dmaTask->bootSize)==-1);
}
