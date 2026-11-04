/* @header
 * func_800C4D70
 * VRAM 0x800C4D70 | ROM 0x714E0 | size 0x2A0
 * asm: asm/nonmatchings/code_80090000/func_800C4D70.s
 */
#include "common.h"

extern s32 D_80038A98, D_800D5F20, D_800EA320, D_800E6B7C, D_800E8204, D_800E8200, D_800EA2D4, D_800EA2D0;
extern s32 D_800EA348, D_800E74D4, D_800E73AC, D_800E73A8, D_800E73A4, D_800E7920, D_800E74F0, D_800E6B60;
extern s32 D_800E753C, D_800D5F18;
extern u8 D_800E74E4, D_800EA2D8;
extern s16 D_800E7C86, D_800E7C84;
extern u8 D_800DF3C8[], D_800DF3E0[], D_800DF4C0[], D_8007E228[];
extern u8 D_800E7C18[][0x10];
void func_80002BA0(void *, void *);
void func_80002C0C(void);
void func_80001260(s32);
void func_80004240(s32);
s32 func_8002B750(void);
void func_800BB2A0(void);
s32 func_800B97CC(s32);
void func_800BA4B4(void);
void func_80005304(void *, f32, f32, f32, f32, f32, f32);
void *func_80093DAC(void *, void *);
void func_800900C0(void *, void *);
void func_80001DC4(void *);
void func_800B5FD0(void);
void func_8002AA28(void);
void func_80098E1C(void);
void func_800B7C20(void);
void func_800C1B24(void);
void func_800A167C(void);
void func_800A98B4(void);
void func_800969E8(void);
void func_80003418(s32);

void func_800C4D70(void) {
    s32 r, i, m;
    u8 *p;

    if (D_80038A98 == 0) {
        D_800D5F20 = 1;
    } else {
        D_800D5F20 = 0;
    }
    func_80002BA0(D_800DF3C8, D_800DF3C8 + 0xC);
    func_80002C0C();
    func_80001260(0x1E0);
    func_80004240(0xF);
    r = func_8002B750();
    func_800BB2A0();
    if (r != 0 && func_800B97CC(6) == 0) {
        func_800BA4B4();
    }
    func_80005304(D_800DF3C8, 0.0f, 400.0f, 500.0f, 0.0f, 150.0f, 0.0f);
    func_80005304(D_800DF3C8 + 0xC, 0.0f, 400.0f, 500.0f, 0.0f, 150.0f, 0.0f);
    func_800900C0(D_800DF4C0, func_80093DAC(D_800DF4C0, D_800DF3E0));
    func_80001DC4(D_800DF3E0);
    func_800B5FD0();
    func_8002AA28();
    func_80098E1C();
    func_800B7C20();
    if (D_80038A98 == 0) {
        func_800C1B24();
    } else {
        func_800A167C();
    }
    func_800A98B4();
    func_800969E8();
    i = 0;
    p = D_800E7C18[0];
    m = -1;
    /* placeholder: a LOOP note here makes `D_800EA320 = 8`'s constant load depend on
       `m = -1`, so sched1 emits i, p, -1, 8 in that order (as the ROM does) */
    do { } while (0);
    D_800EA320 = 8;
    D_800E74E4 = 0x80;
    *(s32 *)(D_8007E228 + 0x60C) = 0;
    D_800E6B7C = 0;
    D_800E8204 = m;
    D_800E8200 = m;
    D_800EA2D4 = 0;
    D_800EA2D0 = 0;
    D_800EA348 = 0;
    D_800E74D4 = 0;
    D_800E73AC = 0;
    D_800E73A8 = 0;
    D_800E73A4 = 0;
    D_800E7920 = 0;
    D_800E7C86 = 0;
    D_800E7C84 = 0;
    D_800E74F0 = 0;
    D_800E6B60 = 0;
    D_800EA2D8 = 0x40;
    D_800E753C = m;
    for (;;) {
        for (r = 0xF; r >= 0; r--) {
            p[r] = 0;
        }
        p += 0x10;
        if (++i >= 4) {
            break;
        }
    }
    D_800D5F18 = 0;
    func_80003418(0x7F);
}
