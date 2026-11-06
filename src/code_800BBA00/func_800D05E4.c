/* @header
 * func_800D05E4
 * VRAM 0x800D05E4 | ROM 0xC3A84 | size 0x11C
 * asm: asm/nonmatchings/code_800BBA00/func_800D05E4.s
 */
#include "common.h"

/* Called by func_800D00FC with (self, opponent) after self's move was set. Needs the opponent's flag 0x02000000
 * and self's move.flags bit 0; otherwise returns 0. By self's grappleCtx: bit 0x400 with 0x40 gives the opponent
 * move 0x45 (and opponent->grappleCtx = 2) when bit 2 is set, else 0x44; bit 0x400 without 0x40, or bit 0x80, sets
 * opponent flag 0x01000000 and gives it move func_800A8D14(self, opponent) from self's table, returning 0; bit
 * 0x100 / 0x200 give move 0x7F / 0x83 (else arg2, which func_800D00FC does not pass). The finishing cases set the
 * move from the opponent's own table, call func_800A7F6C(opponent, 0) and return 1. */
s32 func_800A8D14(Wrestler*,Wrestler*);void func_800A7C40(Wrestler*,s8,s16);void func_800A7F6C(void*,s32);
s32 func_800D05E4(Wrestler *self,Wrestler *opponent,s16 arg2){
    u64 flags=opponent->flags;s32 f;
    if(!(flags&0x02000000))goto ret0;
    if(!(self->move.flags&1))goto ret0;
    f=self->grappleCtx;
    if(f&0x400){if(f&0x40){if(f&2){arg2=0x45;opponent->grappleCtx=2;}else arg2=0x44;goto finish;}
        shared:opponent->flags=flags|0x01000000;func_800A7C40(opponent,self->id,(s16)func_800A8D14(self,opponent));goto ret0;}
    if(f&0x80)goto shared;if(f&0x100)arg2=0x7F;if(f&0x200)arg2=0x83;
    finish:func_800A7C40(opponent,opponent->id,arg2);func_800A7F6C(opponent,0);return 1;
    ret0:return 0;
}
