/* @header
 * osContInit  (originally func_80021230)
 * VRAM 0x80021230 | ROM 0x21E30 | size 0x19C
 * asm: asm/nonmatchings/main/osContInit.s
 */
/* SDK: libultra 2.0I, ultralib src/io/controller.c (same code as the SDK source). */
#include "common.h"

extern s32 D_80037530, D_8006A260, D_8007BD34, D_8007E180;
void osCreateMesgQueue(void *, void *, s32);
s32 osRecvMesg(void *, void *, s32);
void __osContGetInitData(s32, s32);
void __osPackRequestData(s32);
s32 __osSiRawStartDma(s32, void *);
u64 osGetTime(void);
void osSetTimer(void *, u64, u64, void *, void *);
void __osSiCreateAccessQueue(void);
/* One-time controller subsystem init: waits out a boot delay, resets the
 * controller message queue, sets up polling, and stores the passed setup. */
s32 osContInit(void *arg0, s32 arg1, s32 arg2) {
    u8 sp20[0x20]; u8 sp40[0x18]; u8 sp58[8]; s32 result;
    u64 t;
    if(D_80037530) return 0;
    D_80037530=1;
    t=osGetTime();
    if(t < 0x165A0BCULL) {
        osCreateMesgQueue(sp40,sp58,1);
        osSetTimer(sp20,0x165A0BCULL-t,0,sp40,sp58);
        osRecvMesg(sp40,sp58,1);
    }
    D_80070A98=4;
    __osPackRequestData(0);
    __osSiRawStartDma(1,&D_8006A260);
    osRecvMesg(arg0,sp58,1);
    result=__osSiRawStartDma(0,&D_8006A260);
    osRecvMesg(arg0,sp58,1);
    __osContGetInitData(arg1,arg2);
    D_8007BD30=0;
    __osSiCreateAccessQueue();
    osCreateMesgQueue(&D_8007E180,&D_8007BD34,1);
    return result;
}
