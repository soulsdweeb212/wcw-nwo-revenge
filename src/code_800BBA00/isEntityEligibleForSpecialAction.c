/* @header
 * isEntityEligibleForSpecialAction  (originally func_800DA5E8)
 * VRAM 0x800DA5E8 | ROM 0xCDA88 | size 0xF4
 * asm: asm/nonmatchings/code_800BBA00/isEntityEligibleForSpecialAction.s
 */
#include "common.h"

extern u8 D_8007E228[], D_8007EF30[], D_800F9D10[];
s8 func_800D8DF0(void *);
s8 func_800D96A0(void *);
/* Gate for an entity's special action: requires the global 0x200 flag, no
 * global 0x40 inhibit, the entity not flagged 0x200, its link byte different
 * from its own id, and either the high 0x6000 flag word or one of the two
 * state checks. Returns 1 when eligible, else 0. */
s32 isEntityEligibleForSpecialAction(s8 index) {
 u8 *p = D_800F9D10 + index * 0x3B0;
 if (!(*(u16 *)(D_8007E228 + 0x58) & 0x200)) goto ret0;
 if (*(u16 *)(D_8007EF30 + 0x170) & 0x40) goto ret0;
 if (*(u64 *)(p + 0x20) & 0x200) goto ret0;
 if (*(s8 *)(p + 0x355) == *(s8 *)p) goto ret0;
 if (*(u64 *)(p + 0x358) & ((u64)0x6000 << 32)) goto ret1;
 if (func_800D8DF0(p)) goto ret1;
 if (func_800D96A0(p)) goto ret1;
ret0: return 0;
ret1: return 1;
}
