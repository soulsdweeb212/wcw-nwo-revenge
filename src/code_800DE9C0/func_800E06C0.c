#include "common.h"

s32 checkEntityAttackHit(void *, s32);
s32 isEntityActionEligible(void *, void *, s16);
void func_800A6C48(void *, s32);
void func_800E212C(void *);

/* Reaction to an incoming attack: refreshes the entity, and when it can act
 * (action 0x56) starts action 0x44 with state 3 and the pending flag, else
 * action 0x17. Returns 1 when handled. */
s32 func_800E06C0(void *arg0, s32 arg1, s32 arg2) {
    if (arg2 << 24) {
        func_800E212C(arg0);
        if (isEntityActionEligible(arg0, (void *)arg1, 0x56) << 24) {
            func_800A6C48(arg0, 0x44);
            *(s16 *)((u8 *)arg0 + 0xC) = 3;
            *(s32 *)((u8 *)arg0 + 0x2C) = 0x200000;
            return 1;
        }
        func_800A6C48(arg0, 0x17);
        return 1;
    }
    return 0;
}
