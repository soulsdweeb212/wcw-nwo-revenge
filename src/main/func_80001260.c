/* @header
 * func_80001260
 * VRAM 0x80001260 | ROM 0x1E60 | size 0x24C
 * asm: asm/nonmatchings/main/func_80001260.s
 */
#include "common.h"

extern s16 D_8002EEC4;
extern s32 D_80000300;
extern u8 D_8007FC4F;
extern s32 D_8007E228;
typedef struct {u32 words[20];} VideoMode;
extern VideoMode D_80037540,D_80037590;
extern u32 D_80044590[];
extern void *D_800445A0,*D_800445A4,*D_800445A8;
extern u8 D_800445B0[],D_80046760[],D_80046768[],D_80046780[],D_800467C0[],D_800467D8[],D_800467E0[],D_800467F8[],D_80046808[];
extern s32 D_80046810,D_80046828,D_80046830,D_80046844;
extern void *D_80046858;
extern s16 D_80047060,D_80047062,D_80047064,D_80047066;
extern u8 D_3C6D0[],D_3C770[];
extern s32 readRomSynchronousChunks(void *, void *, s32);
extern s32 func_80000580(void *, void *);
extern void *allocateHeap(u32);
extern s32 func_8001C740(s32);
extern s32 func_8001C890(void *, void *, s32);
extern s32 func_8001C8C0(void *, s32, void *, s32, void *, s32);
extern void startThread(void *);
extern s32 func_80020ED0(void *);
extern void setViSpecialFeatures(s32);
extern void func_80021130(s32);
extern s32 func_80021C40(void *, void *, s32);
extern void func_80002CC4(void);
static __inline__ void initRenderQueue(u8 *q) {func_8001C890(q,D_80046780,16);func_80000580(D_80046760,q);}
static __inline__ void setVideoModeFromWidth(s32 *width) {func_80020ED0((u8 *)width-8);}
void func_80001260(void) {
 s32 t; u8 *v; u32 *p; u32 i; s16 two; s32 *width; u8 *q;
 if(D_8002EEC4) {
 D_8002EEC4=0;
 D_8007E228=(s32)(((u32)&D_8007FC4F>>4)<<4);
 readRomSynchronousChunks(D_3C6D0,(void *)D_8007E228,D_3C770-D_3C6D0);
 q=D_80046768;
 initRenderQueue(q);
 q=D_800445B0;
 func_8001C8C0(q,3,func_80002CC4,0,D_80046760,0x46);
 func_8001C890(D_800467C0,D_800467D8,1);
 func_8001C890(D_800467E0,D_800467F8,1);
 startThread(q);
 D_800445A0=allocateHeap(0x400);D_800445A4=allocateHeap(0xC00);D_800445A8=allocateHeap(0x10008);
 if(D_80000300==1) func_80021C40(&D_80037540,D_80046808,0x50);
 else func_80021C40(&D_80037590,D_80046808,0x50);
 t=func_8001C740(0x80401);
 width=&D_80046810;*width=0x1E0;D_80046828=0x300;D_80046830=0x3C0;D_80046844=0x3C0;
 i=0;
 func_8001C740(t);
 setVideoModeFromWidth(width);
 setViSpecialFeatures(0x6A);func_80021130(1);
 two=2;p=D_80044590;
 do {v=allocateHeap(0x4078);p[i]=(u32)v;*(s16 *)(v+0x4058)=two;*(u8 **)(v+0x4050)=D_80046768;*(u32 *)(v+0x4054)=p[i]+(unsigned)0x4058;i += 1;}while(i<4);
 D_80046858=allocateHeap(0x17000);
 }
 D_80047060=0;D_80047062=0;D_80047064=0;D_80047066=0;
}
