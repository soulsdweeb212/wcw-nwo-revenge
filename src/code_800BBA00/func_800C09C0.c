/* @header
 * func_800C09C0
 * VRAM 0x800C09C0 | ROM 0xB3E60 | size 0x484
 * asm: asm/nonmatchings/code_800BBA00/func_800C09C0.s
 */
#include "common.h"

typedef struct {
    u8 p0[4];
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    u8 pE[8];
    s16 f16;
    u8 p18[8];
    u64 flags;
    u8 p28[8];
    u32 f30;
    u8 p34[8];
    s16 f3C;
    s16 f3E;
    u8 p40[0xC];
    f32 f4C;
    u8 p50[8];
    s32 f58;
} Nw2F5CObj;
extern Nw2F5CObj *D_800FAF5C;
extern s32 D_800E3CA0[];
extern f64 D_800E58E0;
extern f64 D_800E58E8;
extern void *D_800F9B00;
void func_800A7364(void *);
void func_800A7D1C(void *, s32);
void beginEntityActionA8D8C(void *);
s8 func_800A9348(void *);
void func_800B68A0(void *, void *, void *);
s16 func_800B6DEC(void *, s32, s32);
s16 func_800BF2FC(void *);
s32 func_800D2B64(void *, f32, u16, s32);
s8 func_800D4198(s16);
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
void func_800D4CC4(void *);
void func_800D7690(void *, s32, s32);
void func_800D7E80(void *, s32);
void func_800D8D74(void *, s32);

void func_800C09C0(void) {
    s16 s0;
    u16 mode;
    s32 anim;

    switch (D_800FAF5C->fC) {
    case 0:
        if (D_800FAF5C->flags & 0x80) {
            D_800FAF5C->flags = (D_800FAF5C->flags & ~0x80ULL) | 0x100ULL;
            D_800FAF5C->f58 = D_800E3CA0[D_800FAF5C->f3C];
            func_800A7364(D_800FAF5C);
            s0 = 0x10B1;
            if (D_800FAF5C->f30 & 0x1000000) {
                s0 = 0x10AC;
            }
            if (D_800FAF5C->f3C == 0) {
                if (D_800E58E0 < D_800FAF5C->f4C) {
                    if (D_800FAF5C->f4C < D_800E58E8) {
                        s0 = 0x10B1;
                    }
                }
            }
        } else {
            D_800FAF5C->flags &= ~0x40ULL;
            if (func_800D4198(0xC8)) {
                D_800FAF5C->flags |= 0x100ULL;
                s0 = 0xF2A;
                if (D_800FAF5C->f30 & 0x1000) {
                    s0 = 0xF29;
                }
            } else {
                D_800FAF5C->flags |= 0x80ULL;
                s0 = 0xF2C;
                if (D_800FAF5C->f30 & 0x1000) {
                    s0 = 0xF2B;
                }
            }
            func_800D7E80(D_800FAF5C, 0);
        }
        func_800D427C(D_800FAF5C, s0, 2);
        D_800FAF5C->fC++;
        break;
    case 1:
        switch (D_800FAF5C->f8) {
        case 0xF29:
        case 0xF2A:
        case 0xF2B:
        case 0xF2C:
            func_800D8D74(D_800FAF5C, 0);
            if (D_800FAF5C->f3E & 1) {
                mode = 0xC00;
            } else {
                mode = 0x300;
            }
            D_800FAF5C->flags |= 0x40ULL;
            func_800D2B64(D_800FAF5C, 2.0f, mode, 0xFFFFE);
            D_800FAF5C->flags &= ~0x40ULL;
            break;
        }
        if (D_800FAF5C->f4 <= 0) {
            func_800D4AD0(D_800FAF5C);
            if (D_800FAF5C->flags & 0x80) {
                func_800A7D1C(D_800FAF5C, 0x12);
                func_800B68A0(D_800FAF5C, D_800F9B00, D_800FAF5C);
                func_800A6C48(D_800FAF5C, 0x2B);
                D_800FAF5C->f16 = func_800B6DEC(D_800FAF5C, 0, 0);
                func_800D7690(D_800FAF5C, 0, 0);
                break;
            }
            switch (D_800FAF5C->f8) {
            case 0x10B1:
                anim = 0x21;
                break;
            case 0x10AC:
                anim = 0x22;
                break;
            default:
                anim = 0x11;
                break;
            }
            func_800A7D1C(D_800FAF5C, anim);
            func_800B68A0(D_800FAF5C, D_800F9B00, D_800FAF5C);
            if (func_800BF2FC(D_800FAF5C) < 0x19 && func_800A9348(D_800FAF5C)) {
                func_800D4CC4(D_800FAF5C);
                if (D_800FAF5C->flags & 0x200000) {
                    s0 = 0xF37;
                } else {
                    s0 = 0xF36;
                }
                func_800D427C(D_800FAF5C, s0, 1);
                D_800FAF5C->fC++;
                break;
            }
            beginEntityActionA8D8C(D_800FAF5C);
        }
        break;
    case 2:
        if (D_800FAF5C->f4 <= 0) {
            func_800D4AD0(D_800FAF5C);
            D_800FAF5C->f16 = func_800B6DEC(D_800FAF5C, 0, 0);
            func_800D7690(D_800FAF5C, 0, 0);
            beginEntityActionA8D8C(D_800FAF5C);
        }
        break;
    }
}
