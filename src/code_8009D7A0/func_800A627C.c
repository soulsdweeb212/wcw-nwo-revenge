#include "common.h"

/* func_800A627C: three-phase action state machine for the entity in
 * D_800EB408. Phase 0 sets up the action resource and sub-action 0x54 and
 * advances, phase 1 advances once the action becomes eligible, and phase 2
 * (when the phase timer runs out) clears the entity's "child" flags
 * (f362 = -1 and flags bit 0x40000000) and releases the action. */
extern void *D_800EB40C;
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800B68A0(void *, void *, void *);
void func_800CE388(void *, s32, void *);
s8 func_800CE6E4(void *, s32);
void func_800D4AD0(void *);
extern s32 D_800F9B24[][4];
extern s8 D_800FADB8;

void func_800A627C(void) {
    u8 *p;
    void *q;

    switch (((Nw2F408 *)D_800EB408)->fC) {
    case 0:
        func_800CE388(D_800EB408, (s32)D_800EB40C, D_800F9B24[D_800FADB8]);
        func_800A7F6C(D_800EB408, 0x54);
        func_800A837C(D_800EB408);
        ((Nw2F408 *)D_800EB408)->fC++;
    case 1:
        if (func_800CE6E4(D_800EB408, D_800F9B24[D_800FADB8][0])) {
            ((Nw2F408 *)D_800EB408)->fC++;
        }
        break;
    case 2:
        if (((Nw2F408 *)D_800EB408)->f4 <= 0) {
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
            p = D_800EB408;
            *(volatile s8 *)(p + 0x362) = -1;
            *(volatile u64 *)(p + 0x20) &= (q = D_800EB408, ~0x40000000ULL);
            func_800D4AD0(q);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
