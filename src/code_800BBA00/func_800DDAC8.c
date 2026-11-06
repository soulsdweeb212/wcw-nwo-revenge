/* @header
 * func_800DDAC8
 * VRAM 0x800DDAC8 | ROM 0xD0F68 | size 0xEF8
 * asm: asm/nonmatchings/code_800BBA00/func_800DDAC8.s
 */
#include "common.h"

extern s8 D_800FADB8;
extern s8 D_800F9870[];
extern s32 D_800F9878[];
extern s32 D_800FABD8;
extern s32 D_800E3F20[];
extern s32 D_800E3CC0[];
extern s8 D_800FABE4;

s16 func_800D5438(void *, s32);
void func_800D427C(void *, s16, s32);
s32 func_800DACE4(void *, void *);
s32 func_800D35B0(s32, s32);
s8 func_800A7240(void *, s32, s32, u64);
void func_800A7F6C(void *, s32);
s8 func_800C2CDC(void *, s32);
s8 tryBeginEntityGrab(void *, void *);
void handleEntityState38To3F(void *, void *);
void func_800DB348(void *, void *);
void func_800A837C(void *);
s32 func_800D3684(s32, s32);
s32 func_800D3550(s32);
void func_800A6BE0(void *, s32);
void func_800D4AD0(void *);
void func_800A7D1C(void *, s32);
s16 func_800B68A0(void *, void *, void *);
s8 func_800D4CC4(void *);
void addEntityHealthDelta(void *, s8);
void beginEntityActionA8D8C(void *);
void func_800D2B64(void *, f32, s32, s32);

#define SLOT D_800F9870[D_800FADB8]

void func_800DDAC8(void)
{
    s32 a;
    s8 r;
    s32 st;
    Wrestler *e;

    st = D_800FAF5C->step;
    D_800FAF5C->flags |= 0x4000000000ULL;
    switch (st) {
    case 0:
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
        D_800F9878[D_800FADB8] = func_800DACE4(D_800FAF5C, D_800F9B00);
        switch ((s16)(D_800FAF5C->state - 0x6B)) {
        case 0:
        case 2:
        case 3:
            if (D_800FAF5C->move.flags & 8) {
                D_800F9878[D_800FADB8] = func_800D35B0(D_800F9878[D_800FADB8], 0x800);
            }
            break;
        case 1:
        case 4:
            if (D_800FAF5C->move.flags & 8) {
                D_800F9878[D_800FADB8] = func_800D35B0(D_800F9878[D_800FADB8], 0x800);
            }
            break;
        }
        func_800D427C(D_800FAF5C, 0xF12, 1);
        D_800FAF5C->step++;
    case 1:
        if (func_800A7240(D_800FAF5C, D_800F9878[D_800FADB8], 0x88, 0)) {
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
            func_800A7F6C(D_800FAF5C, 0);
            D_800FAF5C->step++;
        }
        return;
    case 2:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        if (D_800FAF5C->unk034 & 2) {
            if (D_800F9B00->flags & 0x600000000000ULL) {
                D_800F9B00->flags |= 0x400000;
                D_800F9D10[D_800F9B00->opponentId].flags |= 0x400000;
                SLOT = func_800C2CDC(D_800FAF5C, 0xE);
                D_800F9B00->flags &= ~0x400000ULL;
                D_800F9D10[D_800F9B00->opponentId].flags &= ~0x400000ULL;
            } else {
                SLOT = func_800C2CDC(D_800FAF5C, 0xE);
            }
            if (SLOT != -1) {
                D_800FAF5C->unk034 |= 8;
                if ((D_800F9D10[SLOT].flags & 0x400000) || (D_800F9D10[SLOT].flags & 0x600000000000ULL)) {
                    switch ((s16)(D_800F9D10[SLOT].state - 0x38)) {
                    case 0:
                    case 4:
                    case 6:
                        D_800F9D10[SLOT].pairSignals |= 0x10;
                        D_800FAF5C->unk034 |= 0x20;
                        break;
                    case 1:
                    case 5:
                    case 7:
                        D_800F9D10[D_800F9D10[SLOT].opponentId].pairSignals |= 0x10;
                        D_800FAF5C->unk034 |= 0x20;
                        break;
                    default:
                        D_800F9D10[SLOT].stateTimer += 0x1E;
                        break;
                    }
                } else {
                    D_800FAF5C->unk034 |= 4;
                    handleEntityState38To3F(D_800FAF5C, &D_800F9D10[SLOT]);
                }
                D_800FAF5C->step++;
            }
        } else if ((u16)(D_800FAF5C->state - 0x6E) < 2) {
            r = func_800C2CDC(D_800FAF5C, 0xF);
            SLOT = r;
            if (r != -1) {
                D_800FAF5C->unk034 |= 8;
                handleEntityState38To3F(D_800FAF5C, &D_800F9D10[SLOT]);
                D_800FAF5C->step++;
            }
        } else {
            r = func_800C2CDC(D_800FAF5C, 0xD);
            SLOT = r;
            if (r != -1 && !tryBeginEntityGrab(&D_800F9D10[SLOT], D_800FAF5C)) {
                D_800FAF5C->unk034 |= 8;
                handleEntityState38To3F(D_800FAF5C, &D_800F9D10[SLOT]);
                D_800FAF5C->step++;
            }
        }
    case 3:
        func_800DB348(D_800FAF5C, D_800F9B00);
        if (D_800FAF5C->animFramesLeft > 0) {
            return;
        }
        switch (D_800FAF5C->state) {
        case 0x6C:
        case 0x6F:
            if (D_800FAF5C->flags & 0xC0) {
                D_800FAF5C->y = 90.0f;
            } else {
                D_800FAF5C->y = 0.0f;
            }
            break;
        }
        if (D_800FAF5C->unk034 & 2) {
            if (D_800FAF5C->unk034 & 8) {
                if (D_800FAF5C->unk034 & 4) {
                    func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 1), 1);
                    func_800A837C(D_800FAF5C);
                    D_800FAF5C->step = 4;
                    return;
                }
                if (D_800FAF5C->unk034 & 0x10) {
                    func_800A6C48(&D_800F9D10[SLOT], 0x2C);
                    D_800F9D10[SLOT].step = 7;
                    D_800F9D10[SLOT].opponentId = D_800FADB8;
                    if (D_800FAF5C->move.flags & 0x10) {
                        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 2), 1);
                        D_800FAF5C->step = 6;
                        return;
                    }
                    func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 3), 1);
                    D_800FAF5C->step = 5;
                    return;
                }
                if (D_800FAF5C->state == 0x6D) {
                    func_800A837C(D_800FAF5C);
                    if (D_800FAF5C->unk034 & 0x20) {
                        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 4), 1);
                        D_800FAF5C->step = 4;
                        return;
                    }
                    if (D_800FADB8 != D_800F9D10[SLOT].partnerId) {
                        D_800F9D10[SLOT].opponentId = D_800FADB8;
                    }
                    D_800F9D10[SLOT].heldById = D_800FADB8;
                    a = func_800D3550(func_800D3684(D_800E3CC0[D_800FAF5C->dirIndex], D_800F9B00->heading));
                    if ((D_800FAF5C->unk034 & 1) || SLOT != D_800FABE4 || (D_800F9D10[SLOT].flags & 0x200000) ||
                        (u32)(a - 0x31D) >= 0x1C7) {
                        func_800A6C48(&D_800F9D10[SLOT], 0x57);
                        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 4), 1);
                        D_800FAF5C->step = 4;
                        return;
                    }
                    func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 1), 1);
                    D_800F9B00->lastMoveTakenParam = D_800FAF5C->move.unk3A4;
                    D_800FAF5C->flags |= 0x1060000000ULL;
                    D_800F9B00->flags |= 0x1020000000ULL;
                    D_800FAF5C->attached[0] = D_800FABE4;
                    func_800A6BE0(D_800FAF5C, 0x38);
                    func_800A6BE0(D_800F9B00, 0x39);
                    D_800FAF5C->step = 3;
                    D_800F9B00->step = 3;
                    return;
                }
                func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 1), 1);
                func_800A837C(D_800FAF5C);
                if (!(D_800FAF5C->unk034 & 0x20)) {
                    func_800A6C48(&D_800F9D10[SLOT], 0x57);
                    if (D_800FADB8 != D_800F9D10[SLOT].partnerId) {
                        D_800F9D10[SLOT].opponentId = D_800FADB8;
                    }
                    D_800F9D10[SLOT].heldById = D_800FADB8;
                }
                D_800FAF5C->step = 4;
                return;
            }
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 3), 1);
            D_800FAF5C->step = 5;
            return;
        }
        func_800D4AD0(D_800FAF5C);
        e = D_800FAF5C;
        if (e->unk034 & 8) {
            func_800A6C48(e, 0x2B);
            return;
        }
        func_800A7D1C(e, 0x23);
        func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
        if (func_800D4CC4(e)) {
            addEntityHealthDelta(e, e->move.spiritOnFinish);
        }
        beginEntityActionA8D8C(e);
        return;
    case 4:
        func_800D2B64(D_800FAF5C, 4.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        return;
    case 5:
        func_800D2B64(D_800FAF5C, 4.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            e = D_800FAF5C;
            func_800A7D1C(e, 0x23);
            func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
            if (func_800D4CC4(e)) {
                addEntityHealthDelta(e, e->move.spiritOnFinish);
            }
            beginEntityActionA8D8C(e);
        }
        return;
    case 6:
        func_800D2B64(D_800FAF5C, 4.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800A7D1C(D_800FAF5C, 0x24);
            func_800B68A0(D_800FAF5C, D_800F9B00, D_800FAF5C);
            if (func_800D4CC4(D_800FAF5C)) {
                addEntityHealthDelta(D_800FAF5C, D_800FAF5C->move.spiritOnFinish);
            }
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
        }
        return;
    }
}
