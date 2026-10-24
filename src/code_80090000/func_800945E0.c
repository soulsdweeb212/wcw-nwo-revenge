#include "common.h"

extern s32 D_800E8210,D_800E74C4,D_80038A98;
extern u8 sceneNodeCallback5C50[],D_800C5D10[];
void accumulateColorChannels(s32,s32,s32);void func_80092DE0(void*,s32,u16);void func_8000DEE4(s16);
typedef struct{u32 w0,w1;} Cmd945;
typedef struct {u8 pad[16];void *dl;u8 rest[0xC8];} Obj945;
typedef struct {u8 *src;Obj945 *obj;u32 f8;u16 kind,flag,count,pad[3];} State945;
typedef struct {u32 f0,f4,f8,dl;} Entry945;
typedef struct {u16 idx,count,flags,pad[5];} Rec945;
extern Rec945 *D_800DB684;extern u8 *D_800DB680;extern Obj945 *D_800DB674;extern Entry945 D_800DB6A8[];extern State945 D_800DB8C0[];extern Cmd945 *D_800DB8AC;extern s32 D_800DBD44,D_800DBD54;
#define EMIT945(a,b) {Cmd945 *g=D_800DB8AC++;g->w0=(u32)(a);g->w1=(u32)(b);}
void func_800945E0(s32 arg0){u16 *initial;u16 *saved;Obj945 *obj;Rec945 *p;u16 value;State945 *state;Entry945 *entry;u8 *tail;u32 de;u32 color;s32 i;
p=D_800DB684;state=D_800DB8C0;
if(D_800E8210>=0)initial=*(u16**)(D_800DB680+D_800E8210*4+0x1C);
obj=D_800DB674;D_800DBD44=0;D_800DBD54=-1;value=0;
if(D_800E74C4>0)accumulateColorChannels(1,1,1);
if(p->count){saved=initial;tail=sceneNodeCallback5C50;de=0xDE000000;color=((arg0&255)<<24)|((arg0&255)<<16)|((arg0&255)<<8)|255;
do{if(p->flags&0x8000){if(D_800E74C4<0&&(*(u16*)(state->src+6)&0x2000)){state->count=0;state->obj->dl=tail;state->flag=1;}else{state->obj->dl=D_800DB8AC;state->flag=0;if(D_800E8210>=0)value=*saved;func_80092DE0(state,arg0,value);if(D_800E8210>=0||((state->kind==10)|(state->kind==5)))state->count++;else state->count=0;}state++;}else{u16 index;i=0;obj->dl=D_800DB8AC;index=p->idx;EMIT945(de,D_800C5D10);EMIT945(0xFA000000,color);entry=&D_800DB6A8[index];while(i<p->count){EMIT945(de,entry->dl);i++;entry++;}EMIT945(de,tail);EMIT945(0xDF000000,0);}p++;obj++;}while(p->count);}
if(D_80038A98&&D_800DBD54>=0)func_8000DEE4((s16)D_800DBD54);
}
