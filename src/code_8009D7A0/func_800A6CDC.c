/* @header
 * func_800A6CDC
 * VRAM 0x800A6CDC | ROM 0x9A17C | size 0xA4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A6CDC.s
 */
#include "common.h"

extern u8 D_8007EF30[];
void func_800DECAC(void *, s32, s32, s32);

/* Reset an entity's action to `action`: clears the sub-state/timer fields
 * (entity+0xA/+0xC/+0xE/+0x360), replaces the flag bits 0x10810000000 in the
 * +0x20 u64 with 0x1000000000, reinitialises the action via func_800DECAC, then
 * marks both "linked target" bytes (+0x362/+0x363) as -1 and clears flag
 * 0x40000000. */
void func_800A6CDC(void *entity, s16 action) {
    *(s16 *)((u8 *)entity + 0xA) = action;
    *(s16 *)((u8 *)entity + 0xC) = 0;
    *(s16 *)((u8 *)entity + 0xE) = 0;
    *(s16 *)((u8 *)entity + 0x360) = 0;
    *(u64 *)((u8 *)entity + 0x20) = (*(u64 *)((u8 *)entity + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(entity, 0, 0, 0);
    *(s8 *)((u8 *)entity + 0x362) = -1;
    *(s8 *)((u8 *)entity + 0x363) = -1;
    *(u64 *)((u8 *)entity + 0x20) &= ~0x40000000ULL;
}
