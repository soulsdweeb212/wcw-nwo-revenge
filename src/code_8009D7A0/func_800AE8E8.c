#include "common.h"

typedef struct { s16 f0,f2,f4; u16 f6; s16 f8; u8 pA[8]; s16 f12; u8 p14[14]; s16 f22; u8 p24[10]; u16 f2E; u8 p30[4]; f32 f34; u8 p38[36]; u32 f5C; } ActAE8;
typedef struct { s8 id; u8 p1[9]; s16 fA,fC; u8 pE[26]; u16 f28; } EntAE8;
typedef struct {u8 p[10]; u16 fA;} MatchAE8;
extern ActAE8 *D_800FABD0; extern EntAE8 *D_800FAF58; extern MatchAE8 *D_800F9B60;
extern s16 D_800FABFC[][32],D_800FAC04[][32]; extern f32 D_800FABF8[][16],D_800FAC00[][16]; extern u16 D_800E3CF0[]; extern f64 D_800E51D0;
s16 func_800AEBF0(void); s8 func_800D4198(s16);

/* Three-phase ready-stance/guard chooser for the D_800FABD0 action record.
 * Phase 0 sets the guard animation f6 to 4 and ORs in a direction from
 * D_800E3CF0 (func_800AEBF0's direction) under the f5C bit2 test (D_800FABFC vs
 * D_800FAC04 per-id counts) or a coin flip, then advances.  Phase 1 inspects
 * D_800FAF58's state: on fA==3/fC==2 it may set the dodge animation (16/32) when
 * f34 is under D_800E51D0 and the action is 6/10, else picks the guard (0x4000)
 * when f34 is under the per-id limit from D_800FABF8/D_800FAC00; on fA==4 it
 * advances; otherwise it resets to substate 0 and records the target state f2E
 * from D_800F9B60.  Phase 2 holds animation 0xF00 while D_800FAF58 is state 3,
 * else resets. */
void func_800AE8E8(void) {
 f32 limit; s16 state; s16 direction; s16 action; u16 counter;
 state=D_800FABD0->f4;
 switch(state) {
 case 0:
 D_800FABD0->f6=4; direction=func_800AEBF0();
 if(D_800FABD0->f5C & 2) {
 if(direction!=-1 && D_800FABFC[D_800FAF58->id][0]>D_800FAC04[D_800FAF58->id][0]) D_800FABD0->f6 |= D_800E3CF0[direction];
 } else if(direction!=-1 && func_800D4198(500)) D_800FABD0->f6 |= D_800E3CF0[direction];
 goto advance;
 case 1:
 switch(D_800FAF58->fA) {
 case 3:
 if(D_800FAF58->fC==2) {
 if((f64)D_800FABD0->f34<D_800E51D0 && func_800D4198(D_800FABD0->f12) && ((action=D_800FABD0->f22)==6 || action==10)) {
 if(func_800D4198(500)) D_800FABD0->f6=16; else D_800FABD0->f6=32;
 advance: D_800FABD0->f4++; return;
 }
 if(D_800FAF58->f28&1) limit=D_800FAC00[D_800FAF58->id][0]; else limit=D_800FABF8[D_800FAF58->id][0];
 if(D_800FABD0->f34<limit) {D_800FABD0->f6=0x4000; D_800FABD0->f4++;}
 }
 break;
 case 4: D_800FABD0->f4=state+1; break;
 default: D_800FABD0->f2=0; D_800FABD0->f4=0; D_800FABD0->f2E=D_800F9B60->fA; D_800FABD0->f5C &= ~7; break;
 }
 break;
 case 2:
 if(D_800FAF58->fA==3) D_800FABD0->f8=0xF00;
 else if(D_800FAF58->fA!=4) {D_800FABD0->f2=0; D_800FABD0->f4=0; counter=D_800F9B60->fA; D_800FABD0->f5C &= ~7; D_800FABD0->f2E=counter;}
 break;
 }
}
