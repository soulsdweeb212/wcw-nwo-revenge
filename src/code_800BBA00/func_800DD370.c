#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4, f6, f8, fA, fC, fE;
    u8 pad10[0x10];
    u64 flags;
    u8 pad28[0x32B];
    s8 f353;
    u8 pad354[0x4E];
    s8 f3A2;
    u8 pad3A3[9];
    u32 f3AC;
} Nw2Ent;

#define ACTOR ((Nw2Ent *)D_800FAF5C)
#define PARTNER ((Nw2Ent *)D_800F9B00)

extern void *D_800FAF5C, *D_800F9B00;
extern s32 D_800E3F20[], D_800FABD8;
extern u8 D_800FA0BC[];
extern s8 D_800FADB8;

void func_800A7C40(void *, s8, s16);
void func_800A7D1C(void *, s32);
void func_800A7F6C(void *, s32);
void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
void addEntityHealthDelta(void *, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s8 func_800D4CC4(void *);
s16 func_800D5438(void *, s32);
s32 func_800DACE4(void *, void *);
void func_800DB348(void *, void *);
s8 func_800DB4FC(void *, void *);
s8 isEntityActionEligible(void *, void *, s32);

/* Three-state close-combat action machine on ACTOR->fC.  State 0 selects an
 * animation id (0xE2/0xE3/0xE4/0xEA) from PARTNER's state fA and flags: a partner
 * carrying 0x600000000000 enters a per-state switch (0xE3 for 0x38/39, 0xE2 or
 * 0xE3 for 0x3C..3F depending on the linked entity's flag 0x800000, 0xE2 for
 * 0x72/73, 0xEA for 0x75 when PARTNER->fC<3 and flag 0x40); otherwise
 * isEntityActionEligible / flag 0x400000 pick 0xE4/0xE3/0xE2.  It sends it via
 * func_800A7C40, then runs func_800D427C/func_800A7F6C/func_800DACE4 and advances.
 * State 1 clears ACTOR's entity bit and waits for func_800DB4FC, then falls into
 * state 2, which pumps func_800DB348 and when the s16 timer f4 expires either runs
 * the 0x23 attack (func_800A7D1C/func_800B68A0/func_800D4CC4/addEntityHealthDelta/
 * beginEntityActionA8D8C) or ends with func_800A6C48(0x2B). */
void func_800DD370(void) {
    void *self;
    s16 animId;
    s32 linkedField;

    switch (ACTOR->fC) {
    case 0:
        if (PARTNER->flags & 0x600000000000ULL) {
            animId = 0xE2;
            switch ((s16)(PARTNER->fA - 0x38)) {
            case 0:
            case 1:
                animId = 0xE3;
                break;
            case 4:
            case 5:
            case 6:
            case 7:
                if (PARTNER->flags & 0x200000000000ULL) {
                    linkedField = PARTNER->f3AC;
                } else {
                    linkedField = *(s32 *)((u8 *)D_800FA0BC + (s8)PARTNER->f353 * 0x3B0);
                }
                animId = (linkedField & 0x800000) ? 0xE2 : 0xE3;
                break;
            case 0x3A:
            case 0x3B:
                animId = 0xE2;
                break;
            case 0x3D:
                if (PARTNER->fC < 3 && (PARTNER->flags & 0x40)) {
                    animId = 0xEA;
                }
                break;
            }
        } else {
            if (isEntityActionEligible(ACTOR, D_800F9B00, 0xE4)) {
                animId = 0xE4;
            } else if (PARTNER->flags & 0x400000) {
                animId = 0xE3;
            } else {
                animId = 0xE2;
            }
        }
        func_800A7C40(ACTOR, D_800FADB8, animId);
        func_800D427C(ACTOR, func_800D5438(ACTOR, 0), 3);
        func_800A7F6C(ACTOR, 0);
        func_800DACE4(ACTOR, D_800F9B00);
        ACTOR->fC++;
        break;
    case 1:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        if (func_800DB4FC(ACTOR, D_800F9B00)) {
            ACTOR->fC++;
        }
        /* fallthrough */
    case 2:
        func_800DB348(ACTOR, D_800F9B00);
        if (ACTOR->f4 <= 0) {
            func_800D4AD0(ACTOR);
            self = ACTOR;
            if (((Nw2Ent *)self)->fC == 1) {
                func_800A7D1C(self, 0x23);
                func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
                if (func_800D4CC4(self)) {
                    addEntityHealthDelta(self, *(s8 *)((u8 *)self + 0x3A2));
                }
                beginEntityActionA8D8C(self);
            } else {
                func_800A6C48(self, 0x2B);
            }
        }
        break;
    }
}
