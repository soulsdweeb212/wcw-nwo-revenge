/* @header
 * __amHandleFrameMsg  (originally func_80017018)
 * VRAM 0x80017018 | ROM 0x17C18 | size 0x19C
 * asm: asm/nonmatchings/main/__amHandleFrameMsg.s
 */
/* SDK: the SDK demo audio manager (n64-demos simple/src/main/audiomgr.c) as adapted in this old libmus (SDK code
 * with changes, see docs/sdk_functions.md). */
#include "common.h"

typedef struct { s32 buffer; s16 count,pad6; s32 f8,fC,f10; u8 pad14[0x34]; s32 commands,bytes; u8 pad50[8]; void *queue,*message; u8 pad60[16]; u8 data[1]; } AudioTask;
s32 osScGetCmdQ(s32);
void __clearAudioDMA(void);
s32 n_alAudioFrame(s32,s32*,s32,s16);
s32 osSendMesg(s32,void*,s32);
s32 osVirtualToPhysical(s32);
u32 osAiGetLength(void);
u32 osAiGetStatus(void);
void osAiSetNextBuffer(s32,s32);
extern s32 D_80036F3C,D_80036F48,D_8006252C,D_80062530,D_80062558;
extern s32 D_8006E1A8[];

/* Build and submit one audio task for the current frame.
 * Returns 0 while the AI is still busy (0x80000000) or when no command stream was
 * generated. Otherwise fills `task` from the command list at D_8006E1A8[D_80036F3C]
 * (the buffer flips every task via D_80036F3C ^= 1) and posts it on the audio queue. */
s32 __amHandleFrameMsg(AudioTask *task,AudioTask *previous) {
    s32 generated;
    s32 commandEnd,physical;
    u32 sampleCount;
    if(osAiGetStatus()==0x80000000U) {D_80036F48=1;return 0;}
    __clearAudioDMA();
    sampleCount=osAiGetLength()>>2;
    physical=osVirtualToPhysical(task->buffer);
    if(previous) osAiSetNextBuffer(previous->buffer,previous->count*4);
    if(sampleCount>=0x109 && D_80036F48) {D_80036F48=0;task->count=D_8006252C;}
    else {D_80036F48=1;task->count=D_80062530;}
    commandEnd=n_alAudioFrame(D_8006E1A8[D_80036F3C],&generated,physical,task->count);
    if(!generated) return 0;
    task->queue=(u8*)D_8006E1A8+0x200;
    task->message=task->data;
    task->f8=0;task->f10=2;
    task->commands=D_8006E1A8[D_80036F3C];
    task->bytes=((commandEnd-D_8006E1A8[D_80036F3C])>>3)*8;
    osSendMesg(osScGetCmdQ(D_80062558),&task->f8,1);
    D_80036F3C^=1;
    return 1;
}
