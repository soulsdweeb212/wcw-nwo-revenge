/* @header
 * func_800966D0
 * VRAM 0x800966D0 | ROM 0x42E40 | size 0x1CC
 * asm: asm/nonmatchings/code_80090000/func_800966D0.s
 */
#include "common.h"

/* Per-frame countdown/expiry sweep: mark a fixed block of tasks from the
 * D_800DB4FC module, then walk the real task list and one static array,
 * clearing or setting each task's flag based on its deadline vs frame; finally
 * decay the three shared reaction timers toward zero. */
#ifdef TARGET_PC
/* PC: the objects here are the game's 0xDC-byte scene objects (Nw2SceneObj in common.h), which keep their N64 layout
 * and hold handles (port.h's PTR_TO_SLOT): the N64 view Nw2CounterTask starts at an object's +0x10, so its obj is the
 * object's display list, src its work block (Nw2SceneWork, whose depth the N64 reads at +0x28) and flag its group.
 * The N64 code reaches the overlay's variables through D_800DB4FC: +0x178 is D_800DB674 (the 72 objects), +0x188
 * D_800DB684 (the current list of 16-byte entries) and +0x18C D_800DB688 (its index, -1 for none). On PC the two
 * addresses are variables of their own, so the code reads all three by name. D_800C5A28 + 0x228 is the display list
 * D_800C5C50. The 0x30 records of 0x178 bytes from D_800D6658 + 0x6F8 each start with a scene object. */
extern s16 D_800E74D2[];
extern u8 *D_800DB674;
extern u8 *D_800DB684;
extern s32 D_800DB688;
extern u8 D_800C5C50[];
extern u8 D_800D6658[];
void func_800966D0(s32 frame) {
    Nw2SceneObj *obj; Nw2SceneObj *o; u8 *cursor; u8 *listBase; s16 *lutPtr; f32 *timerPtr; Nw2SceneWork *work; s32 i;
    cursor=D_800DB684;
    if(D_800DB688==-1) {obj=(Nw2SceneObj *)D_800DB674;
        for(i=0;i<0x48;i++){obj[i].dl=PTR_TO_SLOT(D_800C5C50);obj[i].group|=0x80;}
    } else {obj=(Nw2SceneObj *)D_800DB674;
        while(*(u16 *)(cursor+2)) {s16 *d2=D_800E74D2;
            work=SLOT_TO_PTR(obj->work);
            if((s32)work->depth<frame) {if(d2[0]==0)obj->group=6;else obj->group=0;}else obj->group=0;
            cursor+=0x10;obj++;
        }}
    listBase=D_800D6658+0x6F8;
    for(i=0;i<0x30;i++) {lutPtr=D_800E74D2;o=(Nw2SceneObj *)(listBase+i*0x178);
        if(!(o->group&0x80)) {
            timerPtr=&((Nw2SceneWork *)SLOT_TO_PTR(o->work))->depth;
            if((s32)*timerPtr<frame){if(lutPtr[0]==0)o->group=6;else o->group=0;}else o->group=0;
        }}
    if(D_800E74D2[0]) {D_800E74D2[0]=0;
        D_800E74D2[-3]-=24; if(D_800E74D2[-3]<0) D_800E74D2[-3]=0; if(D_800E74D2[0]<D_800E74D2[-3])D_800E74D2[0]=D_800E74D2[-3];
        D_800E74D2[-2]-=24; if(D_800E74D2[-2]<0) D_800E74D2[-2]=0; if(D_800E74D2[0]<D_800E74D2[-2])D_800E74D2[0]=D_800E74D2[-2];
        D_800E74D2[-1]-=24; if(D_800E74D2[-1]<0) D_800E74D2[-1]=0; if(D_800E74D2[0]<D_800E74D2[-1])D_800E74D2[0]=D_800E74D2[-1]; }
}
#else
typedef struct { void *obj; void *src; u8 flag; u8 pad[0xD3]; } Nw2CounterTask;
extern s16 D_800E74D2[];
void D_800DB4FC(void); void D_800C5A28(void); void D_800D6658(void);
void func_800966D0(s32 frame) {
    Nw2CounterTask *rec; u8 *cursor; u8 *listBase; u8 *allocBase; s16 *lutPtr; f32 *timerPtr; s32 value; s32 i;
    value=*(s32 *)((u8 *)D_800DB4FC+0x18C); cursor=*(u8 **)((u8 *)D_800DB4FC+0x188);
    if(value==-1) {allocBase=*(u8 **)((u8 *)D_800DB4FC+0x178); rec=(Nw2CounterTask *)(allocBase+0x10);
        for(i=0;i<0x48;i++){rec[i].obj=(u8 *)D_800C5A28+0x228;rec[i].flag|=0x80;}
    } else {allocBase=*(u8 **)((u8 *)D_800DB4FC+0x178); rec=(Nw2CounterTask *)(allocBase+0x10);
        while(*(u16 *)(cursor+2)) {s16 *d2=D_800E74D2;
            value=(s32)((u8 *)rec->src);
            if((s32)*(f32 *)((u8 *)value+0x28)<frame) {if(d2[0]==0)rec->flag=6;else rec->flag=0;}else rec->flag=0;
            cursor+=0x10;rec=(Nw2CounterTask *)((u8 *)rec+0xDC);
        }}
    listBase=(u8 *)D_800D6658+0x6F8;
    for(i=0;i<0x30;i++) {lutPtr=D_800E74D2;timerPtr=(f32 *)(*(u8 **)(listBase+i*0x178+0x14)+0x28);
        if(!(*(u8 *)(listBase+i*0x178+0x18)&0x80)) {
            if((s32)*timerPtr<frame){if(lutPtr[0]==0)*(u8 *)(listBase+i*0x178+0x18)=6;else *(u8 *)(listBase+i*0x178+0x18)=0;}else *(u8 *)(listBase+i*0x178+0x18)=0;
        }}
    if(D_800E74D2[0]) {D_800E74D2[0]=0;
        D_800E74D2[-3]-=24; if(D_800E74D2[-3]<0) D_800E74D2[-3]=0; if(D_800E74D2[0]<D_800E74D2[-3])D_800E74D2[0]=D_800E74D2[-3];
        D_800E74D2[-2]-=24; if(D_800E74D2[-2]<0) D_800E74D2[-2]=0; if(D_800E74D2[0]<D_800E74D2[-2])D_800E74D2[0]=D_800E74D2[-2];
        D_800E74D2[-1]-=24; if(D_800E74D2[-1]<0) D_800E74D2[-1]=0; if(D_800E74D2[0]<D_800E74D2[-1])D_800E74D2[0]=D_800E74D2[-1]; }
}
#endif
