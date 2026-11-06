/* @header
 * func_800C472C
 * VRAM 0x800C472C | ROM 0xB7BCC | size 0x288
 * asm: asm/nonmatchings/code_800BBA00/func_800C472C.s
 */
#include "common.h"

extern u8 D_8007EF30[];
s8 func_800B71F8(void*,void*,s32);s16 func_800BF2FC(void*);void func_800A6D80(void*,s32);

/* Stun / KO check when attacker's move lands on target. Records the move in target->lastMoveTakenId /
 * lastMoveTakenParam (move.nameId / move.unk3A4) and clears target->koFlags. Value 2 = stun: the move has
 * move.stunBits, target lacks flag 0x400000000 and func_800B71F8(attacker, target, 4) passes. Value 1 = KO: the
 * option bit 1 of D_8007EF30+0x170 is on, the move has move.koBits, target is neither SPECIAL nor on the apron,
 * func_800BF2FC(target) < 25 and func_800B71F8(attacker, 0, 5) passes; then 0x20 is added when target is
 * attacker's tag partner, 0x40 when attacker is SPECIAL and 0x80 when attacker is not LEGAL. On stun or KO,
 * mode adds 4 (mode 0, target in state 20) or 8 (mode 1; mode 2 when anim.endPose >= 7, which is also copied to
 * pose and sets flag 0x200000 for an even pose / clears it for an odd one), the bits are or-ed into koFlags and
 * func_800A6D80 puts target in state 0x2A (stun) or 0x29 (KO); returns 1. Otherwise returns 0.
 * stunBits / koBits are read through s8 pointers: the original tests them with lb (a (s8) cast gives lbu). */
s32 func_800C472C(Wrestler *attacker,Wrestler *target,s16 mode){
    s32 flags,tmp;
    u8 n;
    s8 r;
    target->lastMoveTakenId=attacker->move.nameId;
    target->lastMoveTakenParam=attacker->move.unk3A4;
    flags=0;
    target->koFlags=0;
    if(!(target->flags&0x400000000ULL)&&*(s8 *)&attacker->move.stunBits)flags=(func_800B71F8(attacker,target,4)!=0)*2;
    if((*(u16*)(D_8007EF30+0x170)&1)&&*(s8 *)&attacker->move.koBits&&!(target->flags&(WR_FLAG_SPECIAL|WR_FLAG_ON_APRON))){
        if(func_800BF2FC(target)<25){
            r=func_800B71F8(attacker,0,5);
            tmp=flags|1;
            if(r){
                flags=tmp;
                if(attacker->partnerId==target->id)flags=tmp|0x20;
                if(attacker->flags&WR_FLAG_SPECIAL)flags|=0x40;
                if(!(attacker->flags&WR_FLAG_LEGAL))flags|=0x80;
            }
        }
    }
    if(flags&3){
        switch(mode){
        case 0:if(target->state==20)flags|=4;break;
        case 1:flags|=8;break;
        case 2:
            n=target->anim.endPose;
            target->pose=n;
            if((s8)n>=7){
                flags|=8;
                if(n&1)target->flags&=~0x200000ULL;
                else target->flags|=0x200000ULL;
            }
            break;
        }
        target->koFlags|=flags;
        if(flags&2)func_800A6D80(target,0x2A);
        else func_800A6D80(target,0x29);
        tmp=1;
        return tmp;
    }
    return 0;
}
