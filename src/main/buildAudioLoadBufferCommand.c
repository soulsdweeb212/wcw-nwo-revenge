#include "common.h"

typedef struct {u32 w0,w1;} ACmd19644;
typedef struct {s32 pad[3]; u32 fC,f10; s32 pad14[5]; s32 (*dma)(s32,s32,s32); s32 f2C; s32 pad30[2]; s32 f38,f3C;} Voice19644;
/* Builds an audio DMA command list for voice v: when size>0 a LOADBUFF-style
 * command with the DMA address (8-byte aligned) and the size/offset packed into
 * w0, an optional SETSTATE command (flags bit1), then a command combining
 * v->fC, the flags, arg2 count, alignment and arg4. Clears v->f38 and returns
 * the advanced cursor. */
ACmd19644 *buildAudioLoadBufferCommand(ACmd19644 *dl,Voice19644 *v,s32 arg2,s32 size,u16 arg4,s32 arg5,s32 flags){
 s32 off; s32 address;
 if(size>0){
 address=v->dma(v->f3C,size,v->f2C); off=address&7; size+=off;
 {ACmd19644 *p=dl++; u32 adjust=(size&7)-8; u32 op; p->w0=(((size-adjust)&0xfff)<<12); op=(arg5&0xfff)|0x04000000; p->w0|=op; p->w1=address-off;}
 }else off=0;
 if(flags&2){ACmd19644 *p=dl++; p->w0=0x0f000000;p->w1=v->f10&0x1fffffff;}
 {ACmd19644 *p=dl++;p->w0=(v->fC&0xffffff)|0x01000000;p->w1=(flags<<28)|(((arg2*2)&0xfff)<<16)|(off<<12)|(arg4&0xfff);}
 v->f38=0;return dl;
}
