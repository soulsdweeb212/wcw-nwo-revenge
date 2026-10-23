#include "common.h"

/* Two-stage run/charge action on self D_800EB408:
 * 0) copy the opponent's facing, choose the run animation by whether self is
 *    roughly aligned with it (setting the "turned" bit), then arm the anim;
 * 1) run the move until the timer expires; if the follow-up test fails, clear
 *    the action flag and hand back. */
extern void *D_800EB40C;
void func_800A6C48(void *, s32);
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s8 func_800A83DC(void *, void *);
void func_800B68A0(void *, void *, void *);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
void func_800D7E80(void *, s32);
void func_800D8D74(void *, s32);
extern s32 D_800E3CC0[];
extern s8 D_800FADB8;

void func_800A5BA4(void) {
    u8 *self;
    u8 *opp;
    void *selfCopy;
    u16 facing;
    s16 animId;
    s32 angleDiff;

    switch (((Nw2F408 *)D_800EB408)->fC) {
    case 0:
        opp = D_800EB40C;
        facing = *(u16 *)(opp + 0x3E);
        *(u16 *)((u8 *)D_800EB408 + 0x3E) = facing;
        angleDiff = func_800D3550(func_800D3684(*(s32 *)(opp + 0x58), D_800E3CC0[(s16)facing]));
        if (angleDiff < 0x400) {
            animId = 0x78;
        } else {
            animId = 0x79;
            *(s32 *)((u8 *)D_800EB408 + 0x2C) |= 0x40;
        }
        func_800A7C40(D_800EB408, D_800FADB8, animId);
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 2);
        func_800A7F6C(D_800EB408, 0);
        func_800A837C(D_800EB408);
        func_800D7E80(D_800EB408, 0);
        ((Nw2F408 *)D_800EB408)->fC++;
    case 1:
        func_800D8D74(D_800EB408, 0);
        if (((Nw2F408 *)D_800EB408)->f4 == 1)
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
        if (((Nw2F408 *)D_800EB408)->f4 <= 0) {
            if ((func_800A83DC(D_800EB408, D_800EB40C) << 24) == 0) {
                self = D_800EB408;
                *(volatile s8 *)(self + 0x362) = -1;
                *(volatile u64 *)(self + 0x20) &= (selfCopy = D_800EB408, ~0x40000000ULL);
                func_800D4AD0(selfCopy);
                func_800A6C48(D_800EB408, 0x2B);
            }
        }
        break;
    }
}
