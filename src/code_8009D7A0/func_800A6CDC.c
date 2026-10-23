#include "common.h"

extern u8 D_8007EF30[];
void func_800DECAC(void *, s32, s32, s32);

void func_800A837C(u8 *arg0) {
    s16 t = *(s16 *)(arg0 + 0x388);
    s32 idx;

    if (t != 0x57) {
        idx = (*(s8 *)arg0 * 0x57 + t) * 8;
        if (*(u32 *)(D_8007EF30 + 0x1B4 + idx) < 0xFFFFFFFFU) {
            *(u32 *)(D_8007EF30 + 0x1B4 + idx) += 1;
        }
    }
}

void func_800A6BE0(void *arg0, s16 arg1) {
    *(s16 *)((u8 *)arg0 + 0xA) = arg1;
    *(s16 *)((u8 *)arg0 + 0xC) = 0;
    *(s16 *)((u8 *)arg0 + 0xE) = 0;
    *(s16 *)((u8 *)arg0 + 0x360) = 0;
    *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(arg0, 0, 0, 0);
}

void func_800A6C48(void *arg0, s32 arg1) {
    *(s16 *)((u8 *)arg0 + 0xA) = arg1;
    *(s16 *)((u8 *)arg0 + 0xC) = 0;
    *(s16 *)((u8 *)arg0 + 0xE) = 0;
    *(s16 *)((u8 *)arg0 + 0x360) = 0;
    *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(arg0, 0, 0, 0);
    *(u64 *)((u8 *)arg0 + 0x20) |= 0x10000000ULL;
}

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
