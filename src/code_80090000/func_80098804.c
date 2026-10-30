#include "common.h"

typedef struct{u32 w0,w1;}G988;typedef struct{s32 f0;void*data;s32 f8;s16 w,h,x;}S988;
extern u8 D_C95F0[],D_C95B8[],D_C9678[],D_C9620[];
s32 func_8002AD68(s32);s32 func_8002AE24(s32);s32 func_8002AD34(s32,s32);S988*func_800B600C(s32,s32);void appendPaletteSetupDisplayList(void*);void func_80096D8C(void*,void*,s32,s32,s32,s32,s32,s32,s32);
static __inline__ void draw988(G988**out,s32 resource,s32 x,s32 y,s32 alpha,s32 just){G988*work=*out;S988*s=func_800B600C(resource,8);if(s){appendPaletteSetupDisplayList(&work);if(just==1)x-=s->x;else if(just==2){u16 width=s->x;x-=(s16)width/2;}func_80096D8C(&work,s->data,0,x,y,s->w,s->h,s->w,s->h*(512-alpha)/255);*out=work;}}
#define EMIT988(a,b) {G988*q=(G988*)(p++);q->w0=(a);q->w1=(b);}
void func_80098804(G988**out,s32 id,s32 mode,s32 x,s32 y,s32 alpha){s32 yy,resource;f64 base;G988*p=*out;s32 t0,t1;
EMIT988(0xDE000000,(u32)D_C95F0);EMIT988(0xDE000000,(u32)D_C95B8);EMIT988(0xFA000000,(alpha/2)&255);
t0=(s32)(((y-4)+7.0)*4.0)&65535;t1=(s32)(((y+4)+35.0)*4.0)&65535;
EMIT988(0x02180000,t0|((x-80)<<18));
EMIT988(0x02180002,t0|((x+80)<<18));
EMIT988(0x02180004,t1|((x-80)<<18));
EMIT988(0x02180006,t1|((x+80)<<18));
EMIT988(0xDE000000,(u32)D_C9678);EMIT988(0xDE000000,(u32)D_C9620);EMIT988(0xFA000000,alpha&255);
resource=func_8002AD68(id);base=y;yy=base+21.0;draw988(&p,resource,x-8,yy,alpha,1);draw988(&p,func_8002AE24(id),x+8,yy,alpha,0);draw988(&p,func_8002AD34(id,mode),x,(s32)(base+7.0),alpha,2);*out=p;}
