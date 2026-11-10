/* @header
 * func_800CF1B8
 * VRAM 0x800CF1B8 | ROM 0xC2658 | size 0x1E8
 * asm: asm/nonmatchings/code_800BBA00/func_800CF1B8.s
 */
#include "common.h"

/* Reaction of self to the opponent (called with D_800FAF5C and D_800F9B00).
 * - self on the apron (WR_FLAG_ON_APRON): set grappleCtx bit 0x10, put the root on the apron line
 *   (func_800A7364) and start animation 0x108E (grappleCtx bit 2) or 0x109E.
 * - else, if the opponent has flag 0x100000, a moveMode bit of 0x420, and both share a zone bit
 *   (WR_FLAG_IN_RING | WR_FLAG_ON_FLOOR): set grappleCtx bit 4, set self's move from its own table
 *   (func_800A7C40): 0x56 when grappleCtx bit 0x200000, else 0x4A/0x52 (grappleCtx bit 2; opponent moveMode
 *   0x40 picks the second) or 0x46/0x4E; start the move's animation (func_800D5438) and call func_800A7F6C(self, 0).
 * - else animation 0xEA2 when checkFacingProximity(self, opponent, arg3) passes, otherwise 0xE9F/0xE9E
 *   (grappleCtx bit 1 set; bit 2 picks the first) or 0xE85/0xE84. */
void func_800A7364(Wrestler *);
void func_800A7C40(Wrestler *,s8,s16);
void func_800A7F6C(void *,s32);
s8 checkFacingProximity(Wrestler *,Wrestler *,s32);
void func_800D427C(void *,s16,s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *,s32);
#endif
void func_800CF1B8(Wrestler *self,Wrestler *opponent,s32 arg2,s32 arg3) {
    s32 animId;
    s16 reactionId;
    if (self->flags&WR_FLAG_ON_APRON) {
        self->grappleCtx|=0x10;
        func_800A7364(self);
        func_800D427C(self,(self->grappleCtx&2)?0x108E:0x109E,2);
    } else if ((opponent->flags&0x100000ULL) && (opponent->moveMode&0x420) && (self->flags&opponent->flags&(WR_FLAG_IN_RING|WR_FLAG_ON_FLOOR))) {
        self->grappleCtx|=4;
        if (self->grappleCtx&0x200000) func_800A7C40(self,self->id,0x56);
        else {
            if (self->grappleCtx&2) {
                animId=0x4A;
                if (opponent->moveMode&0x40) animId=0x52;
            } else animId=(opponent->moveMode&0x40)?0x4E:0x46;
            func_800A7C40(self,self->id,animId);
        }
        func_800D427C(self,func_800D5438(self,0),3);
        func_800A7F6C(self,0);
    } else {
        if (checkFacingProximity(self,opponent,arg3)) func_800D427C(self,0xEA2,3);
        else {
            if (self->grappleCtx&1) reactionId=(self->grappleCtx&2)?0xE9F:0xE9E;
            else reactionId=(self->grappleCtx&2)?0xE85:0xE84;
            func_800D427C(self,reactionId,3);
        }
    }
}
