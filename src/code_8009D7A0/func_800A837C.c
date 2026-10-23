#include "common.h"

extern u8 D_8007EF30[];
void func_800DECAC(void *, s32, s32, s32);

/* Bump the per-entity/per-animation usage counter unless the entity is already in
 * state 0x57 (the special "no counter" state). */
void func_800A837C(u8 *entity) {
    s16 t = *(s16 *)(entity + 0x388);
    s32 idx;

    if (t != 0x57) {
        idx = (*(s8 *)entity * 0x57 + t) * 8;
        if (*(u32 *)(D_8007EF30 + 0x1B4 + idx) < 0xFFFFFFFFU) {
            *(u32 *)(D_8007EF30 + 0x1B4 + idx) += 1;
        }
    }
}

/* Reset the entity to a new action state (animation at +0xA, substates +0xC/+0xE,
 * input bits +0x360) and clear the action flags, then notify the action system. */
void func_800A6BE0(void *entity, s16 actionState) {
    *(s16 *)((u8 *)entity + 0xA) = actionState;
    *(s16 *)((u8 *)entity + 0xC) = 0;
    *(s16 *)((u8 *)entity + 0xE) = 0;
    *(s16 *)((u8 *)entity + 0x360) = 0;
    *(u64 *)((u8 *)entity + 0x20) = (*(u64 *)((u8 *)entity + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(entity, 0, 0, 0);
}

/* As func_800A6BE0, but also mark the entity as action-locked (flag 0x10000000). */
void func_800A6C48(void *entity, s32 actionState) {
    *(s16 *)((u8 *)entity + 0xA) = actionState;
    *(s16 *)((u8 *)entity + 0xC) = 0;
    *(s16 *)((u8 *)entity + 0xE) = 0;
    *(s16 *)((u8 *)entity + 0x360) = 0;
    *(u64 *)((u8 *)entity + 0x20) = (*(u64 *)((u8 *)entity + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(entity, 0, 0, 0);
    *(u64 *)((u8 *)entity + 0x20) |= 0x10000000ULL;
}

/* As func_800A6BE0, but also invalidate the two paired-action slots (+0x362/+0x363)
 * and clear the paired-action flag (0x40000000). */
void func_800A6CDC(void *entity, s16 actionState) {
    *(s16 *)((u8 *)entity + 0xA) = actionState;
    *(s16 *)((u8 *)entity + 0xC) = 0;
    *(s16 *)((u8 *)entity + 0xE) = 0;
    *(s16 *)((u8 *)entity + 0x360) = 0;
    *(u64 *)((u8 *)entity + 0x20) = (*(u64 *)((u8 *)entity + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(entity, 0, 0, 0);
    *(s8 *)((u8 *)entity + 0x362) = -1;
    *(s8 *)((u8 *)entity + 0x363) = -1;
    *(u64 *)((u8 *)entity + 0x20) &= ~0x40000000ULL;
}
