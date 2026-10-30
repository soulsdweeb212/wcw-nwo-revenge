/* @header
 * updateEntityPairInteraction  (originally func_800CCE50)
 * VRAM 0x800CCE50 | ROM 0xC02F0 | size 0x5A8
 * asm: asm/nonmatchings/code_800BBA00/updateEntityPairInteraction.s
 */
#include "common.h"

/* updateEntityPairInteraction: decides and starts the paired interaction between
 * two entities (self and other) from their facing flags and current states, then
 * applies the corresponding paired actions.  Returns nonzero when an interaction
 * was started. */

void beginPairedEntityActions(void *, s32, void *, s32);
s32 getEntityPairFacingFlags(void *, void *);
void addEntityHealthDelta(void *, s32);
void func_800E212C(void *);
s32 func_800D7B54(void *, s32, s32, s32);
s32 tryStartFacingGroupAtGate(void *, void *);
void selectPairedActionCD3F8(void *, void *);
void func_800A6C48(void *, s32);
extern s16 D_800FADBE[];

s32 updateEntityPairInteraction(u8 *self, u8 *other) {
    int savedFlags;

    if (getEntityPairFacingFlags(self, other) & 8) {
        *(s32 *)(self + 0x2C) |= 0x40;
    }
    if (*(s16 *)(other + 0xA) == 0x17) {
        addEntityHealthDelta(other, -0xA);
    }
    if (*(u64 *)(other + 0x20) & 0x400000ULL) {
        return 0;
    }
    if ((*(u64 *)(other + 0x20) & 0x600000000000ULL) &&
        !(*(u64 *)(other + 0x20) & 0x0400000000000000ULL)) {
        return 0;
    }
    func_800E212C(other);
    if (*(u64 *)(self + 0x20) & 0x9ULL) {
        goto join;
    }
    if ((*(s16 *)(other + 0xA) == 0xA && ((u16)(*(u16 *)(other + 0xC) - 4) < 2 || *(s16 *)(other + 0xC) == 7)) ||
        (*(s16 *)(other + 0xA) == 0x81 && *(s16 *)(other + 0xC) == 3) ||
        (!(*(u64 *)(other + 0x20) & 0x1000000000ULL) && (u16)(*(s16 *)(other + 0xA) - 0x6B) < 5)) {
        if (!(*(u64 *)(self + 0x20) & 0x40ULL)) {
            return 0;
        }
        if (*(s16 *)(other + 0xA) == 0xA) {
            if (*(s16 *)(other + 0xC) != 4) {
                *(s32 *)(self + 0x2C) = 0;
            } else {
                *(s32 *)(self + 0x2C) = 0x04000000;
            }
        } else {
            *(s32 *)(self + 0x2C) = 0;
        }
        beginPairedEntityActions(self, 0x7B, other, 0x7C);
        goto paired_end;
    }
    if (*(s32 *)(self + 0x2C) & 4) {
        if (*(s32 *)(self + 0x2C) & 0x40) {
            return 0;
        }
        beginPairedEntityActions(self, 0x4F, other, 0x50);
    } else {
        goto rest;
    }
paired_end:
    return 1;
rest:
    if (*(s32 *)(self + 0x2C) & 0x40) {
        goto join;
    }
    if (*(u64 *)(self + 0x20) & *(u64 *)(other + 0x20) & 0x140ULL) {
        if (*(s16 *)(other + 0xA) == 0x5F && *(s16 *)(other + 0xC) < 2) {
            if (*(s16 *)(other + 0x16) < 3) {
                *(s16 *)(self + 0xC) = 5;
                *(s16 *)(other + 0xC) = 2;
            }
            return 0;
        }
        if ((func_800D7B54(other, 0, 0, 3) << 24) != 0) {
            *(s16 *)(self + 0xC) = 5;
            func_800A6C48(other, 0x5F);
            *(s16 *)(other + 0xC) = 2;
            return 0;
        }
    }
    savedFlags = *(s32 *)(self + 0x2C);
    if (savedFlags & 0x40) {
        goto join;
    }
    if (*(u64 *)(self + 0x20) & *(u64 *)(other + 0x20) & 0x140ULL) {
        if (*(s16 *)(other + 0xA) == 0x44 && *(s16 *)(other + 0xC) == 2 &&
            D_800FADBE[*(s8 *)other] < 3) {
            *(s32 *)(self + 0x2C) = savedFlags | 0x100000;
            goto call_update;
        }
        if ((func_800D7B54(other, 0, 0, 4) << 24) != 0) {
            if (*(s16 *)(other + 0xA) == 0x46) {
                goto check74;
            }
            *(s32 *)(self + 0x2C) |= 0x100000;
            selectPairedActionCD3F8(self, other);
            return 1;
        }
    }
join:
    if (*(s16 *)(other + 0xA) != 0x46 && (*(u64 *)(other + 0x20) & 0x1000000000ULL)) {
        return 0;
    }
check74:
    if (*(s16 *)(other + 0xA) == 0x74) {
        return 0;
    }
    if (*(s16 *)(other + 0xA) == 0x46 && (*(s32 *)(other + 0x2C) & 0x100000)) {
        return 0;
    }
    if ((*(u64 *)(self + 0x20) & 0x100ULL) && (*(u64 *)(other + 0x20) & 0x80ULL) &&
        *(s16 *)(other + 0xA) != 0x46) {
        goto call_update;
    }
    if (*(u64 *)(self + 0x20) & 0x9ULL) {
        goto tail;
    }
    if (*(u64 *)(*(void **)(self + 0x364) + 0x38) & 0x400000000ULL) {
        if (*(u64 *)(*(void **)(other + 0x364) + 0x38) & 0x400000000ULL) {
            if (*(s16 *)(self + 0x10) >= 0x97 &&
                *(s16 *)(other + 0x10) >= 0x97 &&
                *(s16 *)(other + 0xA) == 0x44 &&
                *(s16 *)(other + 0xC) == 4 &&
                (*(u64 *)(self + 0x20) & *(u64 *)(other + 0x20) & 0x40ULL) &&
                !(*(s32 *)(self + 0x2C) & 0x44) &&
                !(*(s32 *)(other + 0x2C) & 4) &&
                !(*(s16 *)(other + 0x6) < *(u8 *)(other + 0x370) - 2) &&
                !(*(u8 *)(other + 0x371) < *(s16 *)(other + 0x6))) {
                *(s32 *)(self + 0x2C) |= 0x40000;
                goto call_update;
            }
        }
    }
    if ((tryStartFacingGroupAtGate(self, other) << 16) != 0) {
        return 1;
    }
tail:
    if (*(s16 *)(other + 0xA) != 0x46) {
call_update:
        selectPairedActionCD3F8(self, other);
        return 1;
    }
    return 0;
}
