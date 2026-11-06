/* @header
 * isEntityEligibleForSpecialAction  (originally func_800DA5E8)
 * VRAM 0x800DA5E8 | ROM 0xCDA88 | size 0xF4
 * asm: asm/nonmatchings/code_800BBA00/isEntityEligibleForSpecialAction.s
 */
#include "common.h"

extern u8 D_8007E228[], D_8007EF30[];
s8 func_800D8DF0(void *);
s8 func_800D96A0(void *);
/* Gate for a wrestler's special action: requires the global 0x200 flag, no
 * global 0x40 inhibit, the wrestler not legal (flag 0x200), a tag partner other
 * than itself, and either partnerFlags bits 0x6000 << 32 or one of the two
 * state checks. Returns 1 when eligible, else 0. */
s32 isEntityEligibleForSpecialAction(s8 index) {
    Wrestler *p = &D_800F9D10[index];
    if (!(*(u16 *)(D_8007E228 + 0x58) & 0x200)) goto ret0;
    if (*(u16 *)(D_8007EF30 + 0x170) & 0x40) goto ret0;
    if (p->flags & WR_FLAG_LEGAL) goto ret0;
    if (p->partnerId == p->id) goto ret0;
    if (p->partnerFlags & ((u64)0x6000 << 32)) goto ret1;
    if (func_800D8DF0(p)) goto ret1;
    if (func_800D96A0(p)) goto ret1;
    ret0: return 0;
    ret1: return 1;
}
