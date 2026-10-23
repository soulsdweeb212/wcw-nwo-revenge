#include "common.h"

extern s16 D_80030D38[],D_80030DD4[];
void func_8000327C(s32);
/* Plays sound arg0: ids below 0x4D index D_80030D38, ids 0x4D+ index the 0x34
 * entries of D_80030DD4. Valid (non-negative) ids are played and return 1. */
s32 func_8000DE68(s16 arg0) {
 s16 idx;
 s32 v;
 if(arg0>0) {
 if(arg0<0x4D) v=D_80030D38[arg0];
 else {idx=arg0-0x4D;if(idx>=0x34)return 0;v=D_80030DD4[idx];}
 if(v>=0) {func_8000327C(v);return 1;}
 }
 return 0;
}
extern u32 D_800604C8;extern u8 *D_800604D0; extern s32 *D_800604D8;
s32 func_80015F64(void *,s32,s32,s32,s32);
/* Allocates a voice for channel arg0 (threshold D_800604D8[arg0]): first free
 * voice, else the least-recently-used one below the threshold; returns 0 when
 * none qualifies. */
s32 func_80013994(s32 arg0) {
 u8 *p=D_800604D0,*best;
 s32 threshold=D_800604D8[arg0];
 s32 min=threshold+1;
 u32 i;
 for(i=0;i<D_800604C8;i++,p+=0x158) {
 if(*(s32*)(p+4)==0) return func_80015F64(p,arg0,128,128,threshold);
 if(*(u16*)(p+0xC6)!=0 && *(s32*)(p+0x64)<min) {min=*(s32*)(p+0x64);best=p;}
 }
 if(min<threshold) return func_80015F64(best,arg0,128,128,threshold);
 return 0;
}
extern s32 *D_80036F54;
void func_8002023C(void *);void func_8002021C(void *,void *);
/* Returns the next free audio link node for priority arg1: prefers the spare
 * nodes D_80036F54[5]/[1], else scans the D_80036F54[3] list for a node whose
 * head discriminator is >= arg1 and whose time is zero. */
s32 func_80017700(void **arg0,s16 arg1) {
 s32 r=0; u8 *p;
 p=(u8*)D_80036F54[5];
 if(p!=NULL || (p=(u8*)D_80036F54[1])!=NULL) {
 *arg0=p;func_8002023C(p);func_8002021C(p,(u8*)D_80036F54+12);
 } else {
 p=(u8*)D_80036F54[3];
 while(p!=NULL) {
 if(arg1>=*(s16*)(*(u8**)(p+8)+0x16) && *(s32*)(p+0x88)==0) {
 *arg0=p;r=1;arg1=*(u16*)(*(u8**)(p+8)+0x16);
 }
 p=*(u8**)p;
 }
 }
 return r;
}
s32 *func_80017F18(void); s32 func_80018C24(s32*,s32,s32*);
/* Sends command 16 (with payload arg1&255) to the node referenced by arg0[2]. */
void func_800177D0(s32 *arg0,s32 arg1) {
 s32 *p;
 if(arg0[2]!=0) {
 p=func_80017F18();
 if(p!=0) {
 p[1]=D_80036F54[7]+*(s32*)((u8*)arg0[2]+0x88);
 *(s16*)((u8*)p+8)=16;
 p[3]=arg1&255;p[0]=0;
 func_80018C24((s32*)arg0[2],3,p);
 }
 }
}
