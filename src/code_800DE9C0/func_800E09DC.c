/* @header
 * func_800E09DC
 * VRAM 0x800E09DC | ROM 0xD3E7C | size 0x384
 * asm: asm/nonmatchings/code_800DE9C0/func_800E09DC.s
 */
#include "common.h"

extern u8 *D_800FAF5C,*D_800F9B00;extern f32 D_800F9B0C;extern void *D_800F9B14;extern u16 D_800FABE6;extern s8 D_800FAF78;extern f64 D_800E76F8;
void func_800D25D0(void *,f32);s32 func_800D2B64(void *,f32,u16,s32);s32 func_800D35B0(s32,s32);f32 func_800D3EEC(void *,void *,s32);void func_800D427C(void *,s32,s32);void func_800D4AD0(void *);s32 updateEntityHealthLevel(void *);void func_800E1560(void *,void *);s8 func_800A93C0(void);void beginPairedEntityActions(void *,s32,void *,s32);

/* Try to start a paired grapple between self and partner when the partner's u64
 * flags allow it (0x400000 set, 0x1000000000 clear), the gap is within
 * func_800D3EEC(partner boundary, self) + the f64 D_800E76F8, and the two share
 * one of the common flags 0x140.  On success it starts paired actions 0x3A/0x3B
 * and sets self's byte +0x36 to 0x10 when both the 0xC000 flag bits and self
 * flag 0x80000 are present. */
static inline s32 tryE09(u8 *self,u8 *partner,u16 flags) {
#define Q(p,o) (*(u64 *)((p)+(o)))
 u64 partnerFlags=Q(partner,0x20);f32 distance=D_800F9B0C;u64 selfFlags;
 if(partnerFlags&0x1000000000ULL)return 0;
 if(!(partnerFlags&0x400000))return 0;
 if(!((f64)distance<(f64)func_800D3EEC(partner+0x4C,self+0x6C,*(s32 *)(partner+0x58))+D_800E76F8))return 0;
 selfFlags=Q(self,0x20);
 if(!(selfFlags&Q(partner,0x20)&0x140))return 0;
 if(!(selfFlags&9)||(flags&0xF00)) {
 Q(self,0x20)&=~0x200000000000000ULL;beginPairedEntityActions(self,0x3A,partner,0x3B);self[0x36]=0;
 if((flags&0xC000)==0xC000) {if(Q(self,0x20)&0x80000)self[0x36]=0x10;}
 return 1;
 }
 return 0;
}

/* Five-step paired-grapple/close-in state machine on D_800FAF5C's s16 state
 * (+0xC).  It constantly feeds func_800D25D0/func_800D2B64 with the actor, then:
 * state 0/2 send the range-based animation updateEntityHealthLevel; state 1 waits a beat
 * and starts animation 0xF38; state 3 attempts the paired action (tryE09) or
 * falls back to func_800E1560, optionally bailing via func_800A6C48(0x17); state
 * 4 turns the entity by func_800D35B0(heading, +0x348) and finishes with
 * func_800A6C48(0x2B). */
void func_800E09DC(void) {
#define S(p,o) (*(s16 *)((p)+(o)))
#define W(p,o) (*(s32 *)((p)+(o)))
 func_800D25D0(D_800FAF5C,4.0f);func_800D2B64(D_800FAF5C,2.0f,0,0xFFFFE);
 switch(S(D_800FAF5C,12)) {
 case 0:func_800D427C(D_800FAF5C,(s16)updateEntityHealthLevel(D_800FAF5C),6);S(D_800FAF5C,12)++;break;
 case 1:if(S(D_800FAF5C,4)==1) {func_800D4AD0(D_800FAF5C);func_800D427C(D_800FAF5C,0xF38,1);S(D_800FAF5C,12)=3;}break;
 case 2:
 updateEntityHealthLevel(D_800FAF5C);S(D_800FAF5C,12)++;
 case 3:
 if(!func_800A93C0()) {
 if(D_800FABE6&0x8000) {
 if(tryE09(D_800FAF5C,D_800F9B00,D_800FABE6)) {Q(D_800FAF5C,0x20)|=0x200000000000000ULL;break;}
 }
 if(D_800FAF78) {func_800A6C48(D_800FAF5C,0x17);S(D_800FAF5C,12)=2;break;}
 }
 func_800E1560(D_800FAF5C,D_800F9B14);S(D_800FAF5C,12)++;break;
 case 4:
 W(D_800FAF5C,0x58)=func_800D35B0(W(D_800FAF5C,0x58),W(D_800FAF5C,0x348));
 if(S(D_800FAF5C,4)<=0) {func_800D4AD0(D_800FAF5C);func_800A6C48(D_800FAF5C,0x2B);}break;
 }
#undef S
#undef W
#undef Q
}
