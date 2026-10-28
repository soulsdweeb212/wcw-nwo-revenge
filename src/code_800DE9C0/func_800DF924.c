#include "common.h"

s32 checkEntityAttackHit(void *, s32);
s32 isEntityActionEligible(void *, void *, s16);
void func_800A6C48(void *, s32);
void func_800E212C(void *);

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
