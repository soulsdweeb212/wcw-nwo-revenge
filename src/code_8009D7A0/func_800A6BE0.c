#include "common.h"

extern u8 D_8007EF30[];
void func_800DECAC(void *, s32, s32, s32);

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
