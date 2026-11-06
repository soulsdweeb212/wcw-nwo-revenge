/* @header
 * func_800E1920
 * VRAM 0x800E1920 | ROM 0xD4DC0 | size 0x1B8
 * asm: asm/nonmatchings/code_800DE9C0/func_800E1920.s
 */
#include "common.h"

/* Spawn one particle/effect instance for a wrestler. With bit 4 of the flags
 * argument the wrestler's profile+0x38 must have a bit of 0xC000000000, else
 * nothing happens. Takes a free slot from func_800E2A18, sets w->flags bit
 * 0x1000000000000, records the slot in D_800F99A0[w->id] and fills the slot's
 * type (argument bit 4: 4 if profile+0x38 has 0x4000000000, else 6; otherwise
 * 0 for characterId 0x703, else a random 3..10) and owner id (w->id); with
 * argument bit 2 the type is also copied to D_800F98E1. Types below 6 also set
 * w->flags bit 0x2000000000000. Returns 1 when a slot was filled, else 0. */
s8 func_800E2A18(void); s32 func_800D4148(void);
extern s8 D_800F99A0[]; extern s8 D_800F98E0[][48],D_800F98E1[][48],D_800F98E2[][48];
s32 func_800E1920(Wrestler *w,s32 flags) {
    s8 slot,variant; u16 flagsIn=flags;
    if(!(flags&4) || (*(u64 *)(w->profile+0x38)&0xC000000000ULL)) {
        slot=func_800E2A18();
        if(slot==-1) return 0;
        w->flags|=0x1000000000000ULL;
        D_800F99A0[w->id]=slot;
        if(flagsIn&4) {
            variant=(*(u64 *)(w->profile+0x38)&0x4000000000ULL)?4:6;
        } else {
            variant=0;
            if(w->characterId!=0x703) variant=(s16)func_800D4148()%8+3;
        }
        D_800F98E0[slot][0]=variant;
        if(variant<6) w->flags|=0x2000000000000ULL;
        D_800F98E2[slot][0]=w->id;
        if(flagsIn&2) D_800F98E1[slot][0]=D_800F98E0[slot][0];
        return 1;
    }
    return 0;
}
