#include "common.h"

typedef struct { u8 pad0[12]; s16 state; u8 padE[0x30]; s16 quadrant; u8 pad40[0x2C]; f32 vec[3]; } ObjC18;
extern ObjC18 *D_800FAF5C;
extern s8 D_800FADB8;
extern s32 D_800E3C90[];
extern u16 D_800E3CD0[];
extern void *D_800F9B00;
extern f32 D_800F9B0C;
void func_800A7240(void *,s32,s32,u64);
s32 func_800D6658(void *,void *,u16,s32,f32);
void func_800C18D4(void) {
 s32 q;
 switch(D_800FAF5C->state) {
 case 0:
 q=getXZDirectionQuadrant(D_800FAF5C->vec);
 if(D_800FADB8==2) { switch((s16)q) {case 0:q=3;break;case 1:q=2;break;} }
 else { switch((s16)q) {case 2:q=1;break;case 3:q=0;break;} }
 D_800FAF5C->quadrant=q; D_800FAF5C->state++; break;
 case 1:
 func_800A7240(D_800FAF5C,D_800E3C90[D_800FAF5C->quadrant],0x155,0);
 if(D_800E3CD0[D_800FAF5C->quadrant]&func_800D6658(D_800FAF5C,D_800F9B00,D_800E3CD0[D_800FAF5C->quadrant],0,D_800F9B0C)) func_800A6C48(D_800FAF5C,0x60);
 break;
 }
}
