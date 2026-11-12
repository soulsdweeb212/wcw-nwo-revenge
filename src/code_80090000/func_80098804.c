/* @header
 * func_80098804
 * VRAM 0x80098804 | ROM 0x44F74 | size 0x43C
 * asm: asm/nonmatchings/code_80090000/func_80098804.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx. func_800B600C hands back an entry of the resource-name cache (it looks the
 * name's address up through func_8002A2FC), so S988 follows the entry's PC layout, Nw2ResourceEntryHashed in common.h:
 * the allocation at +8 and the sizes in reserved from +0x10 (N64: +4, +8, +0xC). The display lists at 0x800C95F0,
 * 0x800C95B8, 0x800C9678 and 0x800C9620 are named by their own addresses (D_C95F0 and the others are their N64
 * physical addresses, link constants). port_decls.h declares func_8002AD34, which returns the name's address. */
typedef Gfx G988;typedef struct{ResKey f0;void*data;s32 f8;s16 w,h,x;}S988;
_Static_assert(offsetof(S988,data)==offsetof(Nw2ResourceEntryHashed,allocation)&&offsetof(S988,f8)==offsetof(Nw2ResourceEntryHashed,reserved)&&offsetof(S988,w)==offsetof(Nw2ResourceEntryHashed,reserved)+4&&offsetof(S988,h)==offsetof(Nw2ResourceEntryHashed,reserved)+6&&offsetof(S988,x)==offsetof(Nw2ResourceEntryHashed,reserved)+8,"S988 follows the PC layout of an entry of the resource-name cache");
extern u8 D_800C95F0[],D_800C95B8[],D_800C9678[],D_800C9620[];
s32 func_8002AD68(s32);s32 func_8002AE24(s32);S988*func_800B600C(s32,s32);void appendPaletteSetupDisplayList(void*);void func_80096D8C(void*,void*,s32,s32,s32,s32,s32,s32,s32);
#else
typedef struct{u32 w0,w1;}G988;typedef struct{s32 f0;void*data;s32 f8;s16 w,h,x;}S988;
extern u8 D_C95F0[],D_C95B8[],D_C9678[],D_C9620[];
s32 func_8002AD68(s32);s32 func_8002AE24(s32);s32 func_8002AD34(s32,s32);S988*func_800B600C(s32,s32);void appendPaletteSetupDisplayList(void*);void func_80096D8C(void*,void*,s32,s32,s32,s32,s32,s32,s32);
#endif
static __inline__ void draw988(G988**out,s32 resource,s32 x,s32 y,s32 alpha,s32 just){G988*work=*out;S988*s=func_800B600C(resource,8);if(s){appendPaletteSetupDisplayList(&work);if(just==1)x-=s->x;else if(just==2){u16 width=s->x;x-=(s16)width/2;}func_80096D8C(&work,s->data,0,x,y,s->w,s->h,s->w,s->h*(512-alpha)/255);*out=work;}}
#define EMIT988(a,b) {G988*q=(G988*)(p++);q->w0=(a);q->w1=(b);}
void func_80098804(G988**out,s32 id,s32 mode,s32 x,s32 y,s32 alpha){s32 yy,resource;f64 base;G988*p=*out;s32 t0,t1;
#ifdef TARGET_PC
    /* PC: the display lists' addresses as the whole pointers (port.h's DL_ADDR). */
    EMIT988(0xDE000000,DL_ADDR(D_800C95F0));EMIT988(0xDE000000,DL_ADDR(D_800C95B8));EMIT988(0xFA000000,(alpha/2)&255);
#else
    EMIT988(0xDE000000,(u32)D_C95F0);EMIT988(0xDE000000,(u32)D_C95B8);EMIT988(0xFA000000,(alpha/2)&255);
#endif
    t0=(s32)(((y-4)+7.0)*4.0)&65535;t1=(s32)(((y+4)+35.0)*4.0)&65535;
    EMIT988(0x02180000,t0|((x-80)<<18));
    EMIT988(0x02180002,t0|((x+80)<<18));
    EMIT988(0x02180004,t1|((x-80)<<18));
    EMIT988(0x02180006,t1|((x+80)<<18));
#ifdef TARGET_PC
    EMIT988(0xDE000000,DL_ADDR(D_800C9678));EMIT988(0xDE000000,DL_ADDR(D_800C9620));EMIT988(0xFA000000,alpha&255); /* PC: as above */
#else
    EMIT988(0xDE000000,(u32)D_C9678);EMIT988(0xDE000000,(u32)D_C9620);EMIT988(0xFA000000,alpha&255);
#endif
    resource=func_8002AD68(id);base=y;yy=base+21.0;draw988(&p,resource,x-8,yy,alpha,1);draw988(&p,func_8002AE24(id),x+8,yy,alpha,0);draw988(&p,func_8002AD34(id,mode),x,(s32)(base+7.0),alpha,2);*out=p;}
