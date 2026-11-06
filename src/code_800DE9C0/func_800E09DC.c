/* @header
 * func_800E09DC
 * VRAM 0x800E09DC | ROM 0xD3E7C | size 0x384
 * asm: asm/nonmatchings/code_800DE9C0/func_800E09DC.s
 */
#include "common.h"

extern f32 D_800F9B0C;extern void *D_800F9B14;extern u16 D_800FABE6;extern s8 D_800FAF78;extern f64 D_800E76F8;
void func_800D25D0(void *,f32);s32 func_800D2B64(void *,f32,u16,s32);s32 func_800D35B0(s32,s32);f32 func_800D3EEC(void *,void *,s32);void func_800D427C(void *,s32,s32);void func_800D4AD0(void *);s32 updateEntityHealthLevel(void *);void func_800E1560(void *,void *);s8 func_800A93C0(void);void beginPairedEntityActions(void *,s32,void *,s32);

/* Try to start a paired grapple between self and opponent when the opponent's
 * flags allow it (0x400000 set, 0x1000000000 clear), the gap is within
 * func_800D3EEC(opponent position, self pelvis) + the f64 D_800E76F8, and the two
 * share one of the zone flags 0x140.  On success it starts paired actions
 * 0x3A/0x3B and sets self's unk036 to 0x10 when both the 0xC000 input bits and
 * self flag 0x80000 are present. */
static inline s32 tryE09(Wrestler *self,Wrestler *opponent,u16 flags) {
    u64 opponentFlags=opponent->flags;f32 distance=D_800F9B0C;u64 selfFlags;
    if(opponentFlags&0x1000000000ULL)return 0;
    if(!(opponentFlags&0x400000))return 0;
    if(!((f64)distance<(f64)func_800D3EEC(&opponent->x,&self->jointA[1],opponent->heading)+D_800E76F8))return 0;
    selfFlags=self->flags;
    if(!(selfFlags&opponent->flags&0x140))return 0;
    if(!(selfFlags&9)||(flags&0xF00)) {
        self->flags&=~0x200000000000000ULL;beginPairedEntityActions(self,0x3A,opponent,0x3B);self->unk036=0;
        if((flags&0xC000)==0xC000) {if(self->flags&0x80000)self->unk036=0x10;}
        return 1;
    }
    return 0;
}

/* Five-step paired-grapple/close-in state machine on D_800FAF5C's step.
 * It constantly feeds func_800D25D0/func_800D2B64 with self, then:
 * step 0/2 send the range-based animation updateEntityHealthLevel; step 1 waits a beat
 * and starts animation 0xF38; step 3 attempts the paired action (tryE09) or
 * falls back to func_800E1560, optionally bailing via func_800A6C48(0x17); step
 * 4 turns the wrestler by func_800D35B0(heading, turnPerTick) and finishes with
 * func_800A6C48(0x2B). */
void func_800E09DC(void) {
    func_800D25D0(D_800FAF5C,4.0f);func_800D2B64(D_800FAF5C,2.0f,0,0xFFFFE);
    switch(D_800FAF5C->step) {
    case 0:func_800D427C(D_800FAF5C,(s16)updateEntityHealthLevel(D_800FAF5C),6);D_800FAF5C->step++;break;
    case 1:if(D_800FAF5C->animFramesLeft==1) {func_800D4AD0(D_800FAF5C);func_800D427C(D_800FAF5C,0xF38,1);D_800FAF5C->step=3;}break;
    case 2:
        updateEntityHealthLevel(D_800FAF5C);D_800FAF5C->step++;
    case 3:
        if(!func_800A93C0()) {
            if(D_800FABE6&0x8000) {
                if(tryE09(D_800FAF5C,D_800F9B00,D_800FABE6)) {D_800FAF5C->flags|=0x200000000000000ULL;break;}
            }
            if(D_800FAF78) {func_800A6C48(D_800FAF5C,0x17);D_800FAF5C->step=2;break;}
        }
        func_800E1560(D_800FAF5C,D_800F9B14);D_800FAF5C->step++;break;
    case 4:
        D_800FAF5C->heading=func_800D35B0(D_800FAF5C->heading,D_800FAF5C->turnPerTick);
        if(D_800FAF5C->animFramesLeft<=0) {func_800D4AD0(D_800FAF5C);func_800A6C48(D_800FAF5C,0x2B);}break;
    }
}
