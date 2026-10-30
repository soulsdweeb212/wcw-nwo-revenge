/* @header
 * loadResampledAudioRingBuffer  (originally func_8001FA64)
 * VRAM 0x8001FA64 | ROM 0x20664 | size 0x218
 * asm: asm/nonmatchings/main/func_8001FA64.s
 */
#include "common.h"

typedef struct {u8 pad[0x14];void *state;u8 pad18[8];f32 fraction;u32 flags;} ResampleFA;
typedef struct {s32 start,end;u8 pad8[16];s32 position;u8 pad1C[8];ResampleFA *resample;} OscFA;
typedef struct {u8 pad[24];s32 base;} BufFA;
extern f64 D_8003B880;
void *loadAudioRingBuffer(void *,s32,s32,s32,void *);u32 func_8001CE80(void *);
void *loadResampledAudioRingBuffer(BufFA *obj,OscFA *osc,s32 arg2,s32 n1,void *cmd){f32 rate,whole;s32 n2; s32 span,addr,offset,skip; u16 pitch;u8 flags;s32 *q;
if(osc->resample){span=osc->end-osc->start;rate=(f32)(D_8003B880-(f64)((f32)(s32)(updateTriangleOscillator((f32*)osc,n1)/(f32)span*32768.0f)/32768.0f));whole=osc->resample->fraction+rate*(f32)n1;n2=(s32)whole;osc->resample->fraction=whole-(f32)n2;
addr=obj->base+(osc->position-osc->end)*2;skip=(addr&7)>>1;offset=skip*2;
cmd=loadAudioRingBuffer(obj,addr-offset,0x280,n2+skip,cmd);
q=cmd;cmd=(u8*)cmd+8;q[0]=offset|0x08000280;q[1]=(arg2<<16)|((n1*2)&0xffff);
pitch=(s32)(rate*32768.0f);flags=*(u8*)((u8*)osc->resample+0x27);q=cmd;cmd=(u8*)cmd+8;q[0]=0x05000000|((u32)flags<<16)|pitch;q[1]=func_8001CE80(osc->resample->state);osc->resample->flags=0;{s32 d=n2-n1;osc->position+=d;}
}else cmd=loadAudioRingBuffer(obj,obj->base-osc->end*2,arg2,n1,cmd);return cmd;
}
