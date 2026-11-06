/* @header
 * tryStartPairedEntityActions  (originally func_800E0088)
 * VRAM 0x800E0088 | ROM 0xD3528 | size 0x1A4
 * asm: asm/nonmatchings/code_800DE9C0/tryStartPairedEntityActions.s
 */
#include "common.h"

f32 func_800D3EEC(void *,void *,s32);
void beginPairedEntityActions(void *,s32,void *,s32);
extern f64 D_800E76C0;

/* Try to trigger a paired action of `source` against `target`. Requires target->flags NOT holding 0x1000000000,
 * target flag 0x400000 set, distance below func_800D3EEC(target's position, source's pelvis jointA[1],
 * target->heading) + D_800E76C0, and a shared zone bit (WR_FLAG_IN_RING / WR_FLAG_ON_FLOOR).
 * If source->flags has bit 0x1 or 0x8 and the caller's flags have no 0xF00, refuses.
 * On success clears source flag bit 0x200000000000000, runs actions 0x3A (source) / 0x3B (target), resets
 * source->unk036 (0x10 when flags has all of 0xC000 and source is WR_FLAG_SPECIAL), returns 1. */
s32 tryStartPairedEntityActions(Wrestler *source,Wrestler *target,s32 flags,f32 distance) {
    u16 savedFlags=flags;
    if(target->flags&0x1000000000ULL) return 0;
    if((target->flags&0x400000) && distance<func_800D3EEC(&target->x,&source->jointA[1],target->heading)+D_800E76C0 && (source->flags&target->flags&(WR_FLAG_IN_RING|WR_FLAG_ON_FLOOR))) {
        if((source->flags&9) && !(flags&0xf00)) return 0;
        source->flags&=~0x200000000000000ULL;
        beginPairedEntityActions(source,0x3A,target,0x3B);
        source->unk036=0;
        if((savedFlags&0xC000)==0xC000) {if(source->flags&WR_FLAG_SPECIAL) source->unk036=0x10;}
        return 1;
    }
    return 0;
}
