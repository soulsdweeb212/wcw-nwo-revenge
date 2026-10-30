/* @header
 * func_800CF3A0
 * VRAM 0x800CF3A0 | ROM 0xC2840 | size 0x6B0
 * asm: asm/nonmatchings/code_800BBA00/func_800CF3A0.s
 */
#include "common.h"

typedef struct { u8 pad38[0x38]; u64 flags; } Nw2Attach38;
typedef struct {
    s8 f0; u8 pad1[3]; s16 f4; s16 f6; s16 f8; s16 fA; s16 fC; s16 fE;
    u8 pad10[6]; s16 f16; u8 pad18[8]; u64 flags; u8 pad28[4]; u32 f2C;
    u8 pad30[0x28]; s32 f58; u8 pad5C[0x2E0]; f32 vec[3]; s32 f348;
    u8 pad34C[0x14]; u16 f360; s8 f362; u8 pad363; Nw2Attach38 *f364;
    u8 pad368[0x44]; u32 f3AC;
} Nw2F5CState;
#define O ((Nw2F5CState *)D_800FAF5C)
#define B ((Nw2F5CState *)D_800F9B00)
extern Nw2F5CState *D_800FAF5C;
extern Nw2F5CState *D_800F9B00;
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
extern s8 D_800FADB8;
extern u16 D_800FAF8E[];
extern s16 D_800EB620[];
extern s32 D_800EB600[];
void setupEntityMoveCD990(void *, void *);
s32 func_800CDEE4(void *, void *);
s32 func_800CDF40(void *, u16, u16, s8, u16 *);
s32 func_800D00FC(void *, void *, u16);
void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
s32 func_800D2BAC(void *, void *, f32, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
void func_800A6BE0(void *, s32);
void func_800A7D1C(void *, s32);
void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
void func_800CF3A0(void) {
    s32 ret; s32 inc;
    switch (O->fC) {
    case 0:
        O->flags &= 0xFFFFFFFFF87FFFFFULL;
        setupEntityMoveCD990(O, B);
        O->fC++;
    case 1: {
        Nw2F5CState *o; Nw2F5CState *b;
        o = O; b = B;
        if (o->f16 >= D_800EB620[o->f0]) {
            o->f58 = D_800EB600[o->f0];
            if (o->f2C & 0x100000) o->fC = 7;
            else o->f16 = func_800CDEE4(o, b);
            inc = 1;
        } else {
            translateEntityXZ(o, (u8 *)o + 0x33C);
            o->f58 = func_800D35B0(o->f58, o->f348);
            if (o->f2C & 0x400) func_800D2BAC(o, b, 4.0f, 0xFFFFE);
            o->f16++;
            inc = 0;
        }
        { u16 res; if (res = inc) O->fC++; }
        break;
    }
    case 2:
        ret = func_800CDF40(O, D_800FABE6, D_800FAF8A, D_800FAF78, &D_800FAF8E[(s8)D_800FADB8]);
        if ((s16)ret == 0) break;
        switch ((s16)ret) {
        case 1: O->f360 |= 2; O->fC++; break;
        case 2: O->fC = 7; O->f360 |= 1; break;
        case 3: O->fC = 0xA; O->f360 |= 8; break;
        }
        break;
    case 3: {
        Nw2F5CState **pp;
        pp = &D_800FAF5C;
        *(volatile s16 *)((u8 *)(*pp) + 0xC) += 1;
    case 4:
        ret = func_800D00FC(O, B, D_800FAF8E[(s8)D_800FADB8]);
        if ((s16)ret != 0) {
            if ((s16)ret == 2) { O->f360 &= ~2; O->fC -= 2; }
            if ((s16)ret == 3) { O->f360 |= 4; func_800D427C(O, func_800D5438(B, 1), 1); }
            break;
        }
    }
        if (O->f2C & 0x80) {
            if (O->f3AC & 0x100000) {
                s16 anim;
                if (O->f364->flags & 0x1000000000ULL) anim = 0xEC1;
                else anim = 0xEC1;
                func_800D427C((Nw2F5CState *)(*(u32 *)&D_800FAF5C), anim, 1);
                O->fC++;
                break;
            }
        }
        O->fC = 6;
        O->flags |= 0x10000000ULL;
        break;
    case 5:
        if (O->f4 == 1) O->fC++;
        break;
    case 6:
        if (O->f2C & 0xC0) func_800D427C(O, func_800D5438(O, 0), 1);
        else func_800D427C(O, func_800D5438(O, 0), 3);
        func_800A6BE0(O, 0x49);
        break;
    case 7:
        if (!(O->f2C & 0x380)) func_800D2BEC(O, B, 0, 1.0f, 0, 2);
        if (O->f4 <= 0) {
            Nw2F5CState *o;
            func_800D4AD0(O);
            o = O;
            o->f362 = -1;
            o->flags &= ~0x40000000ULL;
            if (O->f2C & 0x100) { func_800D427C(O, 0x102E, 3); O->fC = 9; }
            else beginEntityActionA8D8C(O);
        }
        break;
    case 8:
        if (O->f4 <= 0) {
            func_800A7D1C(O, 0);
            func_800B68A0(O, B, O);
            func_800D4AD0(O);
            func_800D427C(O, 0xE8F, 1);
        }
        break;
    case 9:
        if (O->f4 <= 0) { func_800D4AD0(O); beginEntityActionA8D8C(O); }
        break;
    case 10:
        func_800D427C(O, 0xEA0, 3);
        O->f360 &= ~8;
        O->fC++;
        break;
    case 11: {
        s16 timer;
        func_800D2BEC(O, B, 0, 1.0f, 0, 2);
        if (O->f4 <= 0) {
            func_800D4AD0(O);
            O->f2C |= 0x40;
            if (B->flags & 0x80000) timer = 0x1E;
            else {
                if (O->f2C & 2) timer = 0x5A; else timer = 0x3C;
                if (O->f2C & 0x300) timer = 0x3C;
            }
            O->f16 = timer;
            func_800D427C(O, 0xE8E, 1);
            O->fC = 2;
        }
        break;
    }
    }
}
