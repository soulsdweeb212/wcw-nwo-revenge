#include "common.h"

/* State handler for the active fighter (D_800EB408) during a hit reaction.
 * While the hit-stun flags (+0x2C & 0x380) are clear it re-issues the attack
 * (func_800D2BEC). If the opponent's flag 0x800000 is clear, the fighter's
 * action id (+0xF6-style byte at 0x6) matches the tracked value at +0x378 and
 * the opponent carries flag 0x1000000, it latches 0x800000, retargets toward
 * the opponent (func_800D5438/func_800D427C), plays sound 0x4A and snapshots
 * D_800FABE4 into +0x351. Otherwise it runs the shared update path
 * (func_800B68A0 / func_800E2500 / func_800E2768) and, once the sub-state
 * (+0x4) is non-positive, ticks func_800A837C; if the AI decision
 * (func_800A83DC) fails it clears flag 0x40000000 and queues action 0x2B. */
extern void *D_800EB40C;
extern u8 D_800FABE4;
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
s16 func_800D5438(void *, s32);
void func_800D427C(void *, s16, s32);
void func_800B68A0(void *, void *, void *);
void func_800A837C(void *);
s8 func_800A83DC(void *, void *);
void func_800D4AD0(void *);
void func_800A6BE0(void *, s32);
void func_800E2500(void *, void *, s32);
void func_800E2768(void *, void *);
void func_800A3428(void) {
    u8 *p; void *q;
    if (!(*(u32 *)((u8 *)D_800EB408 + 0x2C) & 0x380)) func_800D2BEC(D_800EB408, D_800EB40C, 0, 4.0f, 0, 0xFFFFE);
    if (!(*(u64 *)((u8 *)D_800EB40C + 0x20) & 0x800000ULL) && ((Nw2F408 *)D_800EB408)->f6 == *(u8 *)((u8 *)D_800EB408 + 0x378) && (*(u64 *)((u8 *)D_800EB40C + 0x20) & 0x1000000ULL)) {
        *(u64 *)((u8 *)D_800EB408 + 0x20) |= 0x800000ULL;
        func_800D427C(D_800EB408, func_800D5438(D_800EB40C, 1), 1);
        func_800A6BE0(D_800EB408, 0x4A);
        *(u8 *)((u8 *)D_800EB408 + 0x351) = D_800FABE4;
    } else {
        if (((Nw2F408 *)D_800EB408)->f4 == 1) func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
        func_800E2500(D_800EB408, D_800EB40C, 0);
        func_800E2768(D_800EB408, D_800EB40C);
        if (((Nw2F408 *)D_800EB408)->f4 <= 0) {
            func_800A837C(D_800EB408);
            if (!func_800A83DC(D_800EB408, D_800EB40C)) {
                p = D_800EB408;
                *(volatile s8 *)(p + 0x362) = -1;
                *(volatile u64 *)(p + 0x20) &= (q = D_800EB408, ~0x40000000ULL);
                func_800D4AD0(q);
                func_800A6C48(D_800EB408, 0x2B);
            }
        }
    }
}
