#include "common.h"

/* Sub-state machine for the active fighter (D_800FAF5C) while a move is
 * playing. State 0 hides the previous model (func_800A7C40), retargets and
 * caches the target's position (func_800DACE4 into +0x58). State 1 clears the
 * action's flag bits (D_800E3F20 table) and, if func_800DB4FC succeeds, moves
 * on. State 2 runs func_800DB348 and, once the sub-state (+0x4) is non-positive,
 * either starts action 0x23 with the follow-up chain (func_800D4CC4 /
 * addEntityHealthDelta using +0x3A2) or queues action 0x2B. */
extern void *D_800FAF5C, *D_800F9B00;
extern s32 D_800E3F20[], D_800FABD8;
extern s8 D_800FADB8;
void func_800A7C40(void *, s8, s16); void func_800A7D1C(void *, s32); void func_800A7F6C(void *, s32); void beginEntityActionA8D8C(void *); void func_800B68A0(void *, void *, void *); void addEntityHealthDelta(void *, s32); void func_800D427C(void *, s16, s32); void func_800D4AD0(void *); s8 func_800D4CC4(void *); s16 func_800D5438(void *, s32); s32 func_800DACE4(void *, void *); void func_800DB348(void *, void *); s8 func_800DB4FC(void *, void *);
void func_800DCFBC(void) {
    void *p;
    switch (((Nw2F408 *)D_800FAF5C)->fC) {
    case 0:
        func_800A7C40(D_800FAF5C, D_800FADB8, 0xE1);
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
        func_800A7F6C(D_800FAF5C, 0);
        *(s32 *)((u8 *)D_800FAF5C + 0x58) = func_800DACE4(D_800FAF5C, D_800F9B00);
        ((Nw2F408 *)D_800FAF5C)->fC++;
        break;
    case 1:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        if (func_800DB4FC(D_800FAF5C, D_800F9B00)) ((Nw2F408 *)D_800FAF5C)->fC++;
    case 2:
        func_800DB348(D_800FAF5C, D_800F9B00);
        if (((Nw2F408 *)D_800FAF5C)->f4 <= 0) {
            func_800D4AD0(D_800FAF5C); p = D_800FAF5C;
            if (((Nw2F408 *)p)->fC == 1) {
                func_800A7D1C(p, 0x23); func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
                if (func_800D4CC4(p)) addEntityHealthDelta(p, *(s8 *)((u8 *)p + 0x3A2));
                beginEntityActionA8D8C(p);
            } else func_800A6C48(p, 0x2B);
        }
        break;
    }
}
