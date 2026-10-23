#include "common.h"

s32 checkEntityAttackHit(void *, s32);
s32 isEntityActionEligible(void *, void *, s16);
void func_800A6C48(void *, s32);
void func_800E212C(void *);

/* When flag 8 is set, report whether the entity's attack hit arg1. */
s32 func_800E074C(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 & 8) {
        if ((checkEntityAttackHit((void *)arg0, arg1 & 0xFFFF) << 24) != 0) {
            return 1;
        }
    }
    return 0;
}

/* When flag 0x2000 is set and the entity is at health flag 0x80000, clear the flag
 * and reset its health to 0x32. */
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

/* Run the entity's counter-attack reaction when arg2 is set. */
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

/* Report whether the entity is in a vulnerable state. */
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
