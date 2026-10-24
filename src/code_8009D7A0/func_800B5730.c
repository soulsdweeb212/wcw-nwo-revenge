#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s16 state;
    u8 pad1[0x12];
    u64 flags;
    u16 f28;
    u8 pad2[0x2E];
    unsigned long heading;
    u8 pad3[0x10];
    f32 vec[3];
    u8 pad4[0x2EC];
    void *att;
} Nw2Obj5730;

typedef struct {
    u8 pad0[0x38];
    u64 flags;
} Nw2Att5730;

extern u8 D_8007EF30[];
extern f64 D_800E54C8;
extern f64 D_800E54D0;
extern s32 D_800F9B14;
extern void *D_800FAF5C;

void func_800B5F24(void *, void *, u16);
void func_800A6BE0(void *, s32);
void func_800A6C48(void *, s32);
s32 isEntityActionEligible(void *, void *, s32);
s32 func_800B5CA0(void *, void *, u16, f32);
s32 func_800B5DC4(void *, s32);
f32 func_800D3EEC(void *, void *, s32);
s32 func_800D3B24(void *, f32 *, f32, Nw2DirectionResult *);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void getRingBoundaryPointAlongHeading(void *, s32, f32 *);

s32 func_800B5730(Nw2Obj5730 *arg0, Nw2Obj5730 *arg1, u16 arg2, u16 arg3, u8 arg4, f32 arg5) {
    f32 sp10[3];
    register Nw2DirectionResult sp20;
    Nw2Att5730 *att;
    u64 comb;
    f64 d;

    if (arg0->f28 & 0x20) {
        func_800B5F24(arg0, arg1, arg3);
        return 0;
    }
    if (*(u16 *)&D_8007EF30[0x170] & 0x404) goto L5980;
    if (!(arg0->flags & 0x80ULL)) goto L5820;
    if (!(arg1->flags & 0x100ULL)) goto L5820;
    if (!(arg2 & 0x8000)) goto L5820;
    att = arg0->att;
    if (!(att->flags & 0x200000ULL)) goto L5820;
    func_800A6C48(arg0, 0x68);
    return 1;

L5820:
    if (!(arg0->flags & 0x40ULL)) goto L5980;
    if (!(arg1->flags & 0x100ULL)) goto L5980;
    att = arg0->att;
    if (!(att->flags & 0x1800ULL)) goto L5980;
    if (arg4 && (att->flags & 0x80000000ULL) && (arg0->f28 & 1) && !(arg0->f28 & 8)) goto L58D8;
    if (!(arg2 & 0x8000)) goto L5980;

L58D8:
    arg5 = (((Nw2Att5730 *)arg0->att)->flags & 0x1000ULL) ? 390.0f : 180.0f;
    getRingBoundaryPointAlongHeading(arg0->vec, arg0->heading, sp10);
    if ((func_800D3B24(arg0->vec, sp10, arg5, &sp20) << 24) == 0) return 0;
    if ((f64)(arg5 - sp20.y) <= D_800E54C8) {
        func_800A6C48(arg0, 0x63);
        return 1;
    }
    return 0;

L5980:
    if (!((arg0->flags & arg1->flags) & 0x40ULL)) goto L5A28;
    att = arg0->att;
    if (!(att->flags & 0x01000000ULL)) goto L5A28;
    if (!(arg0->f28 & 1)) goto L5A24;
    if (arg0->f28 & 8) goto L5A28;
    if (!(arg3 & 0x8000)) goto L5A2C;
    if ((func_800B5DC4(arg0, 0) << 24) == 0) goto L5A24;
    func_800A6BE0(arg0, 0x6A);
    return 1;

L5A24:
L5A28:
L5A2C:
    if ((func_800B5CA0(arg0, arg1, arg2, arg5) << 24) != 0) return 1;
    if (!(arg0->flags & 0x140ULL)) goto L5C6C;
    comb = arg0->flags & arg1->flags;
    if (!(((comb & 0x40ULL) || (comb & 0x100ULL)) && (arg2 & 0x4000))) goto L5BB0;
    if (!(arg1->flags & 0x200000000000ULL)) goto L5BB0;
    if (arg1->flags & 0x0400000000000000ULL) goto L5BB0;
    d = arg5;
    if (!(d < (f64)func_800D3EEC(arg1->vec, arg0->vec, arg1->heading) + D_800E54D0)) goto L5BB0;
    comb = arg0->flags & arg1->flags;
    if (!((comb & 0x40ULL) || (comb & 0x100ULL))) goto L5BB0;
    if (func_800D3550(func_800D3684(D_800F9B14, arg0->heading)) < 0x200) {
        func_800A6C48(arg0, 0x26);
        return 1;
    }

L5BB0:
    if (arg4) {
        if ((isEntityActionEligible(arg0, arg1, 0x58) << 24) != 0) {
            func_800A6C48(D_800FAF5C, 0x44);
            ((Nw2Obj5730 *)D_800FAF5C)->state = 8;
            return 1;
        }
    }
    if (arg2 & 0x10) {
        func_800A6C48(arg0, 6);
        return 1;
    }
    if (arg2 & 0x20) {
        arg0->state = 4;
        return 1;
    }
    if (arg2 & 0x4000) {
        if (arg0->flags & 0x1000000000000ULL) {
            func_800A6C48(arg0, 8);
        } else {
            func_800A6C48(arg0, 7);
        }
        return 1;
    }
L5C6C:
    if (arg3 & 0xF00) arg0->state = 3;
    return 0;
}
