#include "common.h"

void func_8001C890(void *,void *,s32);
void func_8001C8C0(void *,s32,void (*)(void *),void *,void *,s32);
void func_8001CBF0(s32,void *,s32);
void func_8001CC50(void *,s32);
void startThread(void *);
s32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(s32);
s32 func_80026DB0(void *);
void func_80027F00(void);
s32 startPiRawDma(s32,u32,void *,u32);
void startPiDmaWithHandle(void);
void func_80027B40(void *);
extern s32 D_80037600, D_800389A0;
extern void *D_80037604,*D_80037608,*D_8003760C,*D_80037610;
extern s32 (*D_80037614)(s32,u32,void *,u32);
extern void (*D_80037618)(void);
extern u8 D_800626C0[],D_80062870[],D_80063870[],D_80063888[],D_80073E98[];
/* Create the PI (peripheral interface / cartridge DMA) manager thread.
 * Only sets up once; wires the D_800376xx manager block, temporarily raises
 * thread priority to `priority`, and restores it afterwards. */
void createPiManager(s32 priority,void *queue,void *messages,s32 count) {
 s32 oldPriority, mask, savedPriority;
 s32 *active=&D_80037600;
 if(*active==0) {
 cachePiDomainTimings();
 func_8001C890(queue,messages,count);
 func_8001C890(D_80063870,D_80063888,1);
 if(D_800389A0==0) func_80027F00();
 func_8001CBF0(8,D_80063870,0x22222222);
 savedPriority=-1;
 oldPriority=func_80026DB0(0);
 if(oldPriority<priority) {savedPriority=oldPriority;func_8001CC50(0,priority);}
 mask=nw2DisableInterrupts();
 *active=1;
 D_80037610=D_80073E98;
 D_80037614=startPiRawDma;
 D_80037618=startPiDmaWithHandle;
 D_8003760C=D_80063870;
 D_80037604=D_800626C0;
 D_80037608=queue;
 func_8001C8C0(D_800626C0,0,func_80027B40,active,D_80062870+0x1000,priority);
 startThread(D_800626C0);
 nw2RestoreInterrupts(mask);
 if(savedPriority!=-1) func_8001CC50(0,savedPriority);
 }
}
