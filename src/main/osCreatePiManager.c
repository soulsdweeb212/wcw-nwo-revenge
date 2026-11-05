/* @header
 * osCreatePiManager  (originally func_800255B0)
 * VRAM 0x800255B0 | ROM 0x261B0 | size 0x1A0
 * asm: asm/nonmatchings/main/osCreatePiManager.s
 */
/* SDK: libultra 2.0I, ultralib src/io/pimgr.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

void osCreateMesgQueue(void *,void *,s32);
void osCreateThread(void *,s32,void (*)(void *),void *,void *,s32);
void osSetEventMesg(s32,void *,s32);
void osSetThreadPri(void *,s32);
void osStartThread(void *);
s32 __osDisableInt(void);
void __osRestoreInt(s32);
s32 osGetThreadPri(void *);
void __osPiCreateAccessQueue(void);
s32 osPiRawStartDma(s32,u32,void *,u32);
void osEPiRawStartDma(void);
void __osDevMgrMain(void *);
extern s32 __osPiDevMgr, __osPiAccessQueueEnabled;
extern void *D_80037604,*D_80037608,*D_8003760C,*D_80037610;
extern s32 (*D_80037614)(s32,u32,void *,u32);
extern void (*D_80037618)(void);
extern u8 piThread[],D_80062870[],piEventQueue[],piEventBuf[],__osPiAccessQueue[];
/* Create the PI (peripheral interface / cartridge DMA) manager thread.
 * Only sets up once; wires the D_800376xx manager block, temporarily raises
 * thread priority to `priority`, and restores it afterwards. */
void osCreatePiManager(s32 priority,void *queue,void *messages,s32 count) {
    s32 oldPriority, mask, savedPriority;
    s32 *active=&__osPiDevMgr;
    if(*active==0) {
        createSpeedParam();
        osCreateMesgQueue(queue,messages,count);
        osCreateMesgQueue(piEventQueue,piEventBuf,1);
        if(__osPiAccessQueueEnabled==0) __osPiCreateAccessQueue();
        osSetEventMesg(8,piEventQueue,0x22222222);
        savedPriority=-1;
        oldPriority=osGetThreadPri(0);
        if(oldPriority<priority) {savedPriority=oldPriority;osSetThreadPri(0,priority);}
        mask=__osDisableInt();
        *active=1;
        D_80037610=__osPiAccessQueue;
        D_80037614=osPiRawStartDma;
        D_80037618=osEPiRawStartDma;
        D_8003760C=piEventQueue;
        D_80037604=piThread;
        D_80037608=queue;
        osCreateThread(piThread,0,__osDevMgrMain,active,D_80062870+0x1000,priority);
        osStartThread(piThread);
        __osRestoreInt(mask);
        if(savedPriority!=-1) osSetThreadPri(0,savedPriority);
    }
}
