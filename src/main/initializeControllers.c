#include "common.h"

extern s32 D_80037530, D_8006A260, D_8007BD34, D_8007E180;
void func_8001C890(void *, void *, s32);
s32 func_8001C990(void *, void *, s32);
void func_800213CC(s32, s32);
void func_80021480(s32);
s32 func_80025810(s32, void *);
u64 func_80026DD0(void);
void func_80026FA0(void *, u64, u64, void *, void *);
void func_800276F0(void);
/* One-time controller subsystem init: waits out a boot delay, resets the
 * controller message queue, sets up polling, and stores the passed setup. */
s32 initializeControllers(void *arg0, s32 arg1, s32 arg2) {
 u8 sp20[0x20]; u8 sp40[0x18]; u8 sp58[8]; s32 result;
 u64 t;
 if(D_80037530) return 0;
 D_80037530=1;
 t=func_80026DD0();
 if(t < 0x165A0BCULL) {
 func_8001C890(sp40,sp58,1);
 func_80026FA0(sp20,0x165A0BCULL-t,0,sp40,sp58);
 func_8001C990(sp40,sp58,1);
 }
 D_80070A98=4;
 func_80021480(0);
 func_80025810(1,&D_8006A260);
 func_8001C990(arg0,sp58,1);
 result=func_80025810(0,&D_8006A260);
 func_8001C990(arg0,sp58,1);
 func_800213CC(arg1,arg2);
 D_8007BD30=0;
 func_800276F0();
 func_8001C890(&D_8007E180,&D_8007BD34,1);
 return result;
}
