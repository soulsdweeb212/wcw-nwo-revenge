#include "common.h"

extern u8 D_8007EF30[];
void func_800DECAC(void *, s32, s32, s32);

/* Increments the usage counter for the entity's current animation pair
 * (id*0x57 + anim), saturating at 0xFFFFFFFF. */
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

/* Sets the entity's animation state arg1, clears its substate/timer/input fields
 * and replaces the action flags with 0x1000000000. */
void func_800A6BE0(void *arg0, s16 arg1) {
    *(s16 *)((u8 *)arg0 + 0xA) = arg1;
    *(s16 *)((u8 *)arg0 + 0xC) = 0;
    *(s16 *)((u8 *)arg0 + 0xE) = 0;
    *(s16 *)((u8 *)arg0 + 0x360) = 0;
    *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(arg0, 0, 0, 0);
}

/* Like func_800A6BE0 but also raises the 0x10000000 flag. */
void func_800A6C48(void *arg0, s32 arg1) {
    *(s16 *)((u8 *)arg0 + 0xA) = arg1;
    *(s16 *)((u8 *)arg0 + 0xC) = 0;
    *(s16 *)((u8 *)arg0 + 0xE) = 0;
    *(s16 *)((u8 *)arg0 + 0x360) = 0;
    *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(arg0, 0, 0, 0);
    *(u64 *)((u8 *)arg0 + 0x20) |= 0x10000000ULL;
}

/* Like func_800A6BE0 but also clears the two partner ids and the 0x40000000
 * flag. */
void func_800A6CDC(void *arg0, s16 arg1) {
    *(s16 *)((u8 *)arg0 + 0xA) = arg1;
    *(s16 *)((u8 *)arg0 + 0xC) = 0;
    *(s16 *)((u8 *)arg0 + 0xE) = 0;
    *(s16 *)((u8 *)arg0 + 0x360) = 0;
    *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(arg0, 0, 0, 0);
    *(s8 *)((u8 *)arg0 + 0x362) = -1;
    *(s8 *)((u8 *)arg0 + 0x363) = -1;
    *(u64 *)((u8 *)arg0 + 0x20) &= ~0x40000000ULL;
}
