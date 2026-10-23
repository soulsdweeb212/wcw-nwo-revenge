#include "common.h"

/* Three-state reach/hold action on self D_800EB408:
 * 0) copy the opponent's facing; if the opponent is in the special state jump
 *    straight to state 2 and set the flag, else arm the animation and advance;
 * 1) run the hold until the timer expires, then finish and, if the facings
 *    still match, have the opponent react;
 * 2) run the alternate 4-frame hold and finish. */
void beginEntityActionA8D8C(void *); void func_800C472C(void *,void *,s32);
s32 func_800D2B64(void *,f32,u16,s32);
s32 func_800D2BEC(void *,void *,void *,f32,u16,s32);
void func_800D427C(void *,s16,s32); void func_800D4AD0(void *);
s16 func_800D5438(void *,s32); void func_800D7E80(void *,void *); void func_800D8D74(void *,s32);
extern void *D_800EB40C;
#define F(p,t,o) (*(t *)((u8 *)(p)+(o)))
void func_800A4274(void) {
 switch(F(D_800EB408,s16,0xC)) {
 case 0:
 F(D_800EB408,u16,0x386)=F(D_800EB40C,u16,0x386);
 if(F(D_800EB40C,u32,0x3AC)&0x01000000) {
 F(D_800EB408,s16,0xC)=2;
 F(D_800EB408,u64,0x20)|=0x10000000ULL;
 return;
 }
 func_800D427C(D_800EB408,func_800D5438(D_800EB40C,1),2);
 func_800D7E80(D_800EB408,D_800EB40C);
 F(D_800EB408,s16,0xC)++;
 case 1:
 func_800D8D74(D_800EB408,0);
 func_800D2BEC(D_800EB408,D_800EB40C,0,4.0f,0,0xFFFFE);
 if(F(D_800EB408,s16,4)<=0) {
 func_800D4AD0(D_800EB408); beginEntityActionA8D8C(D_800EB408);
 if(F(D_800EB408,s16,0x386)==F(D_800EB40C,s16,0x386)) func_800C472C(D_800EB40C,D_800EB408,2);
 }
 break;
 case 2:
 func_800D2B64(D_800EB408,4.0f,0,0xFFFFE);
 if(F(D_800EB408,s16,4)<=0) {func_800D4AD0(D_800EB408);beginEntityActionA8D8C(D_800EB408);}
 break;
 }
}
