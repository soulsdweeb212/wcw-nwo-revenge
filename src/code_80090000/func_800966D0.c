#include "common.h"

/* Per-frame countdown/expiry sweep: mark a fixed block of tasks from the
 * D_800DB4FC module, then walk the real task list and one static array,
 * clearing or setting each task's flag based on its deadline vs frame; finally
 * decay the three shared reaction timers toward zero. */
typedef struct { void *obj; void *src; u8 flag; u8 pad[0xD3]; } Nw2CounterTask;
extern s16 D_800E74D2[];
void func_800DB4FC(void); void func_800C5A28(void); void func_800D6658(void);
void func_800966D0(s32 frame) {
 Nw2CounterTask *rec; u8 *cursor; u8 *listBase; u8 *allocBase; s16 *lutPtr; f32 *timerPtr; s32 value; s32 i;
 value=*(s32 *)((u8 *)func_800DB4FC+0x18C); cursor=*(u8 **)((u8 *)func_800DB4FC+0x188);
 if(value==-1) {allocBase=*(u8 **)((u8 *)func_800DB4FC+0x178); rec=(Nw2CounterTask *)(allocBase+0x10);
 for(i=0;i<0x48;i++){rec[i].obj=(u8 *)func_800C5A28+0x228;rec[i].flag|=0x80;}
 } else {allocBase=*(u8 **)((u8 *)func_800DB4FC+0x178); rec=(Nw2CounterTask *)(allocBase+0x10);
 while(*(u16 *)(cursor+2)) {s16 *d2=D_800E74D2;
 value=(s32)((u8 *)rec->src);
 if((s32)*(f32 *)((u8 *)value+0x28)<frame) {if(d2[0]==0)rec->flag=6;else rec->flag=0;}else rec->flag=0;
 cursor+=0x10;rec=(Nw2CounterTask *)((u8 *)rec+0xDC);
 }}
 listBase=(u8 *)func_800D6658+0x6F8;
 for(i=0;i<0x30;i++) {lutPtr=D_800E74D2;timerPtr=(f32 *)(*(u8 **)(listBase+i*0x178+0x14)+0x28);
 if(!(*(u8 *)(listBase+i*0x178+0x18)&0x80)) {
 if((s32)*timerPtr<frame){if(lutPtr[0]==0)*(u8 *)(listBase+i*0x178+0x18)=6;else *(u8 *)(listBase+i*0x178+0x18)=0;}else *(u8 *)(listBase+i*0x178+0x18)=0;
 }}
 if(D_800E74D2[0]) {D_800E74D2[0]=0;
 D_800E74D2[-3]-=24; if(D_800E74D2[-3]<0) D_800E74D2[-3]=0; if(D_800E74D2[0]<D_800E74D2[-3])D_800E74D2[0]=D_800E74D2[-3];
 D_800E74D2[-2]-=24; if(D_800E74D2[-2]<0) D_800E74D2[-2]=0; if(D_800E74D2[0]<D_800E74D2[-2])D_800E74D2[0]=D_800E74D2[-2];
 D_800E74D2[-1]-=24; if(D_800E74D2[-1]<0) D_800E74D2[-1]=0; if(D_800E74D2[0]<D_800E74D2[-1])D_800E74D2[0]=D_800E74D2[-1]; }
}
