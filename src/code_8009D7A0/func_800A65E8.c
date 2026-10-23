#include "common.h"

/* Two-state follow-up/victory handler for the active fighter (D_800EB408).
 * State 0 re-issues the move (func_800D2B64) and sets pose 0xE7B. State 1,
 * once the sub-state (+0x4) is spent, releases the move and queues action 3,
 * then picks the win/taunt pose (0xE7B id 10 or 11 via func_800D4D44)
 * depending on D_800FABE6 bit 2, clearing the action's flag 0x1000000 in the
 * first case. While moving it may face the nearest valid opponent
 * (func_800D26A0/func_800D2600). */
extern void *D_800FAF5C;
extern u16 D_800FABE6;
s32 func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
void func_800D2600(void *, s32, f32);
s16 func_800D4D44(void *, s32, s32);
s8 func_800D26A0(void *, void *, s32);
void func_800A65E8(void) {
    s8 id;
    func_800D2B64(D_800EB408, 1.0f, 0, 2);
    switch (((Nw2F408 *)D_800EB408)->fC) {
    case 0:
        func_800D427C(D_800EB408, 0xE7B, 3);
        ((Nw2F408 *)D_800EB408)->fC++;
        break;
    case 1:
        id = func_800D26A0(D_800FAF5C, 0, -1);
        if (id != -1 && !(*(u64 *)(D_800F9D30 + id * 0x3B0) & 0x400000ULL)) func_800D2600(D_800FAF5C, -1, 2.0f);
        if (((Nw2F408 *)D_800EB408)->f4 <= 0) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 3);
            if (D_800FABE6 & 4) {
                func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 10, 0), 3);
                ((Nw2F408 *)D_800EB408)->fC = 2;
                *(u64 *)((u8 *)D_800EB408 + 0x20) &= ~0x1000000ULL;
            } else {
                func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 11, 0), 3);
                ((Nw2F408 *)D_800EB408)->fC = 3;
            }
        }
        break;
    }
}
