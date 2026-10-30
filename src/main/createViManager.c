/* @header
 * createViManager  (originally func_800258C0)
 * VRAM 0x800258C0 | ROM 0x264C0 | size 0x1A0
 * asm: asm/nonmatchings/main/createViManager.s
 */
#include "common.h"

typedef struct {s32 flag; void *f4,*f8,*fC; s32 f10,f14,f18,f1C;} Nw2DmaState;
extern Nw2DmaState D_80037630;
extern s32 D_8003764C;
extern u8 D_80063A50[];
extern s32 D_80063898,D_80064A50,D_80064A68;
extern s16 D_80064A80,D_80064A98;
extern s8 D_80064A82,D_80064A9A;
extern s32 D_80064A84,D_80064A9C;
void func_8001C890(void*,void*,s32);
void func_8001C8C0(void*,s32,void*,Nw2DmaState*,void*,s32);
void func_8001CBF0(s32,void*,s16*);
void func_8001CC50(s32,s32);
s32 startThread(void*);
s32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(s32);
s32 func_80026DB0(s32);
void func_80027040(void); void func_800274D0(void); void func_80025A60(void);

/* libultra createViManager: on first call, initialise the vertical-interrupt
 * manager (message queue + two retrace event messages), raise the VI thread
 * priority to `pri` (restoring the old one afterwards) and start the manager
 * thread whose entry point is func_80025A60. */
void createViManager(s32 arg0) {
 s32 savedPriority; s16 *retraceMsg13,*retraceMsg14;
 if(D_80037630.flag==0) {
 do {savedPriority=-1;} while(0); func_80027040(); D_8003764C=0;
 func_8001C890(&D_80064A50,&D_80064A68,5);
 retraceMsg13=&D_80064A80; *retraceMsg13=13; D_80064A82=0; D_80064A84=0;
 retraceMsg14=&D_80064A98; *retraceMsg14=14; D_80064A9A=0; D_80064A9C=0;
 func_8001CBF0(7,&D_80064A50,retraceMsg13); func_8001CBF0(3,&D_80064A50,retraceMsg14);
 {s32 r=func_80026DB0(0); if(r<arg0) {savedPriority=r; func_8001CC50(0,arg0);}}
 {s32 mask=nw2DisableInterrupts(); D_80037630.flag=1;
 D_80037630.f4=&D_80063898; D_80037630.f8=&D_80064A50; D_80037630.fC=&D_80064A50;
 D_80037630.f10=0; D_80037630.f14=0; D_80037630.f18=0;
 func_8001C8C0(&D_80063898,0,&func_80025A60,&D_80037630,D_80063A50+0x1000,arg0);
 func_800274D0(); startThread(&D_80063898); nw2RestoreInterrupts(mask);}
 if(savedPriority!=-1) func_8001CC50(0,savedPriority);
 }
}
