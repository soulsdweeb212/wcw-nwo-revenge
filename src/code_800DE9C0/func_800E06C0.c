#include "common.h"

s32 checkEntityAttackHit(void *, s32);
s32 isEntityActionEligible(void *, void *, s16);
void func_800A6C48(void *, s32);
void func_800E212C(void *);

/* Returns 1 when the attack-hit check (for the 8 bit in arg2) passes. */
s32 func_800E074C(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 & 8) {
        if ((checkEntityAttackHit((void *)arg0, arg1 & 0xFFFF) << 24) != 0) {
            return 1;
        }
    }
    return 0;
}

/* Clears the entity's 0x80000 flag and resets its +0x14 counter to 0x32 when
 * arg1 bit 0x2000 is set. */
void func_800E0780(void *arg0, s32 arg1) {
    u64 f;

    if (arg1 & 0x2000) {
        f = *(u64 *)((u8 *)arg0 + 0x20);
        if (f & 0x80000) {
            *(u64 *)((u8 *)arg0 + 0x20) = f & ~0x80000ULL;
            *(s16 *)((u8 *)arg0 + 0x14) = 0x32;
        }
    }
}

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

/* Returns 1 when the entity is downed (0x80000) or its attachment is flagged
 * 0x20000 or arg1 is in state 0x75. */
s32 func_800DF924(void *arg0, void *arg1) {
    s32 r = 0;
    void *p;

    if (*(u64 *)((u8 *)arg0 + 0x20) & 0x80000) {
        r = 1;
    }
    p = *(void **)((u8 *)arg0 + 0x364);
    if ((*(u64 *)((u8 *)p + 0x38) & 0x20000) || *(s16 *)((u8 *)arg1 + 0xA) == 0x75) {
        r = 1;
    }
    return r;
}
