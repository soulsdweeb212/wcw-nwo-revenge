/* @header
 * func_800DDAC8
 * VRAM 0x800DDAC8 | ROM 0xD0F68 | size 0xEF8
 * asm: asm/nonmatchings/code_800BBA00/func_800DDAC8.s
 */
#include "common.h"

typedef struct {
    u8 pad0[4];
    s16 f4;
    u8 pad6[4];
    s16 fA;
    s16 fC;
    u8 padE[8];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u8 pad28[0xC];
    u8 f34;
    u8 pad35[9];
    s16 f3E;
    u8 pad40[6];
    s16 f46;
    u8 pad48[8];
    f32 f50;
    u8 pad54[4];
    s32 f58;
    u8 pad5C[0x2F5];
    s8 f351;
    u8 pad352;
    s8 f353;
    u8 pad354;
    s8 f355;
    u8 pad356[0xA];
    u16 f360;
    s8 f362;
    u8 pad363[0x3F];
    s8 f3A2;
    u8 pad3A3;
    s8 f3A4;
    u8 pad3A5[7];
    u32 f3AC;
} EntD0;

extern EntD0 *D_800FAF5C;
extern EntD0 *D_800F9B00;
extern EntD0 D_800F9D10[];
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
void func_800A6C48(void *, s32);
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
#define ME D_800FAF5C
#define OT D_800F9B00

void func_800DDAC8(void)
{
    s32 a;
    s8 r;
    s32 st;
    EntD0 *e;

    st = ME->fC;
    ME->flags |= 0x4000000000ULL;
    switch (st) {
    case 0:
        func_800D427C(ME, func_800D5438(ME, 0), 1);
        D_800F9878[D_800FADB8] = func_800DACE4(ME, OT);
        switch ((s16)(ME->fA - 0x6B)) {
        case 0:
        case 2:
        case 3:
            if (ME->f3AC & 8) {
                D_800F9878[D_800FADB8] = func_800D35B0(D_800F9878[D_800FADB8], 0x800);
            }
            break;
        case 1:
        case 4:
            if (ME->f3AC & 8) {
                D_800F9878[D_800FADB8] = func_800D35B0(D_800F9878[D_800FADB8], 0x800);
            }
            break;
        }
        func_800D427C(ME, 0xF12, 1);
        ME->fC++;
    case 1:
        if (func_800A7240(ME, D_800F9878[D_800FADB8], 0x88, 0)) {
            func_800D427C(ME, func_800D5438(ME, 0), 3);
            func_800A7F6C(ME, 0);
            ME->fC++;
        }
        return;
    case 2:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        if (ME->f34 & 2) {
            if (OT->flags & 0x600000000000ULL) {
                OT->flags |= 0x400000;
                D_800F9D10[OT->f353].flags |= 0x400000;
                SLOT = func_800C2CDC(ME, 0xE);
                OT->flags &= ~0x400000ULL;
                D_800F9D10[OT->f353].flags &= ~0x400000ULL;
            } else {
                SLOT = func_800C2CDC(ME, 0xE);
            }
            if (SLOT != -1) {
                ME->f34 |= 8;
                if ((D_800F9D10[SLOT].flags & 0x400000) || (D_800F9D10[SLOT].flags & 0x600000000000ULL)) {
                    switch ((s16)(D_800F9D10[SLOT].fA - 0x38)) {
                    case 0:
                    case 4:
                    case 6:
                        D_800F9D10[SLOT].f360 |= 0x10;
                        ME->f34 |= 0x20;
                        break;
                    case 1:
                    case 5:
                    case 7:
                        D_800F9D10[D_800F9D10[SLOT].f353].f360 |= 0x10;
                        ME->f34 |= 0x20;
                        break;
                    default:
                        D_800F9D10[SLOT].f16 += 0x1E;
                        break;
                    }
                } else {
                    ME->f34 |= 4;
                    handleEntityState38To3F(ME, &D_800F9D10[SLOT]);
                }
                ME->fC++;
            }
        } else if ((u16)(ME->fA - 0x6E) < 2) {
            r = func_800C2CDC(ME, 0xF);
            SLOT = r;
            if (r != -1) {
                ME->f34 |= 8;
                handleEntityState38To3F(ME, &D_800F9D10[SLOT]);
                ME->fC++;
            }
        } else {
            r = func_800C2CDC(ME, 0xD);
            SLOT = r;
            if (r != -1 && !tryBeginEntityGrab(&D_800F9D10[SLOT], ME)) {
                ME->f34 |= 8;
                handleEntityState38To3F(ME, &D_800F9D10[SLOT]);
                ME->fC++;
            }
        }
    case 3:
        func_800DB348(ME, OT);
        if (ME->f4 > 0) {
            return;
        }
        switch (ME->fA) {
        case 0x6C:
        case 0x6F:
            if (ME->flags & 0xC0) {
                ME->f50 = 90.0f;
            } else {
                ME->f50 = 0.0f;
            }
            break;
        }
        if (ME->f34 & 2) {
            if (ME->f34 & 8) {
                if (ME->f34 & 4) {
                    func_800D427C(ME, func_800D5438(ME, 1), 1);
                    func_800A837C(ME);
                    ME->fC = 4;
                    return;
                }
                if (ME->f34 & 0x10) {
                    func_800A6C48(&D_800F9D10[SLOT], 0x2C);
                    D_800F9D10[SLOT].fC = 7;
                    D_800F9D10[SLOT].f353 = D_800FADB8;
                    if (ME->f3AC & 0x10) {
                        func_800D427C(ME, func_800D5438(ME, 2), 1);
                        ME->fC = 6;
                        return;
                    }
                    func_800D427C(ME, func_800D5438(ME, 3), 1);
                    ME->fC = 5;
                    return;
                }
                if (ME->fA == 0x6D) {
                    func_800A837C(ME);
                    if (ME->f34 & 0x20) {
                        func_800D427C(ME, func_800D5438(ME, 4), 1);
                        ME->fC = 4;
                        return;
                    }
                    if (D_800FADB8 != D_800F9D10[SLOT].f355) {
                        D_800F9D10[SLOT].f353 = D_800FADB8;
                    }
                    D_800F9D10[SLOT].f351 = D_800FADB8;
                    a = func_800D3550(func_800D3684(D_800E3CC0[ME->f3E], OT->f58));
                    if ((ME->f34 & 1) || SLOT != D_800FABE4 || (D_800F9D10[SLOT].flags & 0x200000) ||
                        (u32)(a - 0x31D) >= 0x1C7) {
                        func_800A6C48(&D_800F9D10[SLOT], 0x57);
                        func_800D427C(ME, func_800D5438(ME, 4), 1);
                        ME->fC = 4;
                        return;
                    }
                    func_800D427C(ME, func_800D5438(ME, 1), 1);
                    OT->f46 = ME->f3A4;
                    ME->flags |= 0x1060000000ULL;
                    OT->flags |= 0x1020000000ULL;
                    ME->f362 = D_800FABE4;
                    func_800A6BE0(ME, 0x38);
                    func_800A6BE0(OT, 0x39);
                    ME->fC = 3;
                    OT->fC = 3;
                    return;
                }
                func_800D427C(ME, func_800D5438(ME, 1), 1);
                func_800A837C(ME);
                if (!(ME->f34 & 0x20)) {
                    func_800A6C48(&D_800F9D10[SLOT], 0x57);
                    if (D_800FADB8 != D_800F9D10[SLOT].f355) {
                        D_800F9D10[SLOT].f353 = D_800FADB8;
                    }
                    D_800F9D10[SLOT].f351 = D_800FADB8;
                }
                ME->fC = 4;
                return;
            }
            func_800D427C(ME, func_800D5438(ME, 3), 1);
            ME->fC = 5;
            return;
        }
        func_800D4AD0(ME);
        e = ME;
        if (e->f34 & 8) {
            func_800A6C48(e, 0x2B);
            return;
        }
        func_800A7D1C(e, 0x23);
        func_800B68A0(ME, ME, ME);
        if (func_800D4CC4(e)) {
            addEntityHealthDelta(e, e->f3A2);
        }
        beginEntityActionA8D8C(e);
        return;
    case 4:
        func_800D2B64(ME, 4.0f, 0, 0xFFFFE);
        if (ME->f4 <= 0) {
            func_800D4AD0(ME);
            func_800A6C48(ME, 0x2B);
        }
        return;
    case 5:
        func_800D2B64(ME, 4.0f, 0, 0xFFFFE);
        if (ME->f4 <= 0) {
            func_800D4AD0(ME);
            e = ME;
            func_800A7D1C(e, 0x23);
            func_800B68A0(ME, ME, ME);
            if (func_800D4CC4(e)) {
                addEntityHealthDelta(e, e->f3A2);
            }
            beginEntityActionA8D8C(e);
        }
        return;
    case 6:
        func_800D2B64(ME, 4.0f, 0, 0xFFFFE);
        if (ME->f4 <= 0) {
            func_800A7D1C(ME, 0x24);
            func_800B68A0(ME, OT, ME);
            if (func_800D4CC4(ME)) {
                addEntityHealthDelta(ME, ME->f3A2);
            }
            func_800D4AD0(ME);
            beginEntityActionA8D8C(ME);
        }
        return;
    }
}
