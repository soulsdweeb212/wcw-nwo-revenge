#include "common.h"

typedef struct { s32 buffer; s16 count,pad6; s32 f8,fC,f10; u8 pad14[0x34]; s32 commands,bytes; u8 pad50[8]; void *queue,*message; u8 pad60[16]; u8 data[1]; } AudioTask;
s32 func_80000E00(s32);
void func_80017408(void);
s32 writeAudioStreamBuffer(s32,s32*,s32,s16);
s32 func_8001CAC0(s32,void*,s32);
s32 func_8001CE80(s32);
u32 func_80020A80(void);
u32 func_80020A90(void);
void func_80020AA0(s32,s32);
extern s32 D_80036F3C,D_80036F48,D_8006252C,D_80062530,D_80062558;
extern s32 D_8006E1A8[];

/* Build and submit one audio task for the current frame.
 * Returns 0 while the AI is still busy (0x80000000) or when no command stream was
 * generated. Otherwise fills `task` from the command list at D_8006E1A8[D_80036F3C]
 * (the buffer flips every task via D_80036F3C ^= 1) and posts it on the audio queue. */
s32 createAudioTask(AudioTask *task,AudioTask *previous) {
 s32 generated;
 s32 commandEnd,physical;
 u32 sampleCount;
 if(func_80020A90()==0x80000000U) {D_80036F48=1;return 0;}
 func_80017408();
 sampleCount=func_80020A80()>>2;
 physical=func_8001CE80(task->buffer);
 if(previous) func_80020AA0(previous->buffer,previous->count*4);
 if(sampleCount>=0x109 && D_80036F48) {D_80036F48=0;task->count=D_8006252C;}
 else {D_80036F48=1;task->count=D_80062530;}
 commandEnd=writeAudioStreamBuffer(D_8006E1A8[D_80036F3C],&generated,physical,task->count);
 if(!generated) return 0;
 task->queue=(u8*)D_8006E1A8+0x200;
 task->message=task->data;
 task->f8=0;task->f10=2;
 task->commands=D_8006E1A8[D_80036F3C];
 task->bytes=((commandEnd-D_8006E1A8[D_80036F3C])>>3)*8;
 func_8001CAC0(func_80000E00(D_80062558),&task->f8,1);
 D_80036F3C^=1;
 return 1;
}
