/* @header
 * tryStartPairedEntityActions  (originally func_800E0088)
 * VRAM 0x800E0088 | ROM 0xD3528 | size 0x1A4
 * asm: asm/nonmatchings/code_800DE9C0/func_800E0088.s
 */
#include "common.h"

f32 func_800D3EEC(void *,void *,s32);
void beginPairedEntityActions(void *,s32,void *,s32);
extern f64 D_800E76C0;

/* Try to trigger a paired (tag) action against `target`. Requires target u64 flags
 * +0x20 NOT holding 0x1000000000, target bit 0x400000 set, the XZ distance within
 * its boundary+margin, and the two entities' common flags masked with 0x140 nonzero.
 * If the source already has bit 9 and the caller's flags have no 0xF00, refuses.
 * On success clears source bit 0x200000000000000, runs actions 0x3A/0x3B, resets
 * source[0x36] (0x10 when 0xC000 flags and source bit 0x80000), returns 1. */
s32 tryStartPairedEntityActions(u8 *source,u8 *target,s32 flags,f32 distance) {
 u16 savedFlags=flags;
 if(*(u64 *)(target+0x20)&0x1000000000ULL) return 0;
 if((*(u64 *)(target+0x20)&0x400000) && distance<func_800D3EEC(target+0x4C,source+0x6C,*(s32 *)(target+0x58))+D_800E76C0 && (*(u64 *)(source+0x20)&*(u64 *)(target+0x20)&0x140)) {
 if((*(u64 *)(source+0x20)&9) && !(flags&0xf00)) return 0;
 *(u64 *)(source+0x20)&=~0x200000000000000ULL;
 beginPairedEntityActions(source,0x3A,target,0x3B);
 source[0x36]=0;
 if((savedFlags&0xC000)==0xC000) {if(*(u64 *)(source+0x20)&0x80000) source[0x36]=0x10;}
 return 1;
 }
 return 0;
}
