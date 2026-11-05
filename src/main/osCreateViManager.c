/* @header
 * osCreateViManager  (originally func_800258C0)
 * VRAM 0x800258C0 | ROM 0x264C0 | size 0x1A0
 * asm: asm/nonmatchings/main/osCreateViManager.s
 */
/* SDK: libultra 2.0I, ultralib src/io/vimgr.c (same code as the SDK source). */
#include "common.h"

typedef struct {s32 flag; void *f4,*f8,*fC; s32 f10,f14,f18,f1C;} Nw2DmaState;
extern Nw2DmaState __osViDevMgr;
extern s32 __additional_scanline;
extern u8 D_80063A50[];
extern s32 viThread,viEventQueue,viEventBuf;
extern s16 viRetraceMsg,viCounterMsg;
extern s8 D_80064A82,D_80064A9A;
extern s32 D_80064A84,D_80064A9C;
void osCreateMesgQueue(void*,void*,s32);
void osCreateThread(void*,s32,void*,Nw2DmaState*,void*,s32);
void osSetEventMesg(s32,void*,s16*);
void osSetThreadPri(s32,s32);
s32 osStartThread(void*);
s32 __osDisableInt(void);
void __osRestoreInt(s32);
s32 osGetThreadPri(s32);
void __osTimerServicesInit(void); void __osViInit(void); void viMgrMain(void);

/* libultra osCreateViManager: on first call, initialise the vertical-interrupt
 * manager (message queue + two retrace event messages), raise the VI thread
 * priority to `pri` (restoring the old one afterwards) and start the manager
 * thread whose entry point is viMgrMain. */
void osCreateViManager(s32 arg0) {
    s32 savedPriority; s16 *retraceMsg13,*retraceMsg14;
    if(__osViDevMgr.flag==0) {
        do {savedPriority=-1;} while(0); __osTimerServicesInit(); __additional_scanline=0;
        osCreateMesgQueue(&viEventQueue,&viEventBuf,5);
        retraceMsg13=&viRetraceMsg; *retraceMsg13=13; D_80064A82=0; D_80064A84=0;
        retraceMsg14=&viCounterMsg; *retraceMsg14=14; D_80064A9A=0; D_80064A9C=0;
        osSetEventMesg(7,&viEventQueue,retraceMsg13); osSetEventMesg(3,&viEventQueue,retraceMsg14);
        {s32 r=osGetThreadPri(0); if(r<arg0) {savedPriority=r; osSetThreadPri(0,arg0);}}
        {s32 mask=__osDisableInt(); __osViDevMgr.flag=1;
            __osViDevMgr.f4=&viThread; __osViDevMgr.f8=&viEventQueue; __osViDevMgr.fC=&viEventQueue;
            __osViDevMgr.f10=0; __osViDevMgr.f14=0; __osViDevMgr.f18=0;
            osCreateThread(&viThread,0,&viMgrMain,&__osViDevMgr,D_80063A50+0x1000,arg0);
            __osViInit(); osStartThread(&viThread); __osRestoreInt(mask);}
        if(savedPriority!=-1) osSetThreadPri(0,savedPriority);
    }
}
