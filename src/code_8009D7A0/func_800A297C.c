#include "common.h"

void func_800D25D0(void *, f32);
s32 func_800D2B64(void *, f32,u16,s32);
void func_800D427C(void *,s16,s32);
void func_800D4AD0(void *);
void func_800D7B54(void *,u16,u16,s32);
extern u16 D_800FABE6,D_800FAF8A;
/* Three-state action on D_800EB408: runs the boundary correction, plays the
 * intro animation 0xF61, then (after the timer) animation 0xF62, and finally
 * tears the action down and returns to action 0x2B. */
void func_800A297C(void) {
 func_800D25D0(D_800EB408,4.0f);
 func_800D2B64(D_800EB408,2.0f,0,0xFFFFE);
 func_800D7B54(D_800EB408,D_800FABE6,D_800FAF8A,1);
 switch(((Nw2F408 *)D_800EB408)->fC) {
 case 1:
 if(((Nw2F408 *)D_800EB408)->f4<=0) {
 func_800D427C(D_800EB408,0xF62,1);
 ((Nw2F408 *)D_800EB408)->fC++;
 }
 break;
 case 0:
 func_800D427C(D_800EB408,0xF61,1);
 ((Nw2F408 *)D_800EB408)->fC++;
 break;
 case 2:
 if(((Nw2F408 *)D_800EB408)->f4<=0) {
 func_800D4AD0(D_800EB408);
 func_800A6C48(D_800EB408,0x2B);
 }
 break;
 }
}
