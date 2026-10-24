#include "common.h"

typedef struct { s8 f0; u8 pad1[3]; s16 f4; u8 pad6[2]; s16 f8; s16 fA; s16 fC; s16 fE; u8 pad10[4]; s16 f14; s16 f16; s16 f18; u8 pad1A[6]; u64 flags; u8 pad28[0x1C]; s16 f44; u8 pad46[0x12]; s32 f58; u8 pad5C[0x304]; u16 f360; s8 f362; u8 pad363[0x49]; u32 f3AC; } Nw2F5C;
extern void *D_800FAF5C;
extern void *D_800F9B00;
extern f32 D_800F9B0C;
extern volatile s32 D_800F9B14;
extern s8 D_800FADB8;
extern u8 D_800FACF8[];
extern s32 D_800EB520[];

s32 func_800D35B0(s32, s32);
void func_800D427C(void *, s16, s32);
void func_800D3E40(void *, void *, s32, void *);
void func_800D4AD0(void *);
s16 func_800D4D44(void *, s32, f32);
s16 func_800D5438(void *, s32);
s16 func_800D7128(void *, void *, void *, void *);
void beginEntityActionA8D8C(void *);
s32 func_800A7240(void *, s32, s32, u64);
s32 stepEntityXZQuadraticSpline(void *, void *);

#define O ((Nw2F5C *)D_800FAF5C)
#define B ((Nw2F5C *)D_800F9B00)

void func_800C78F0(void) {
    switch (O->fC) {
    case 0:
        do { O->flags |= 0x1000000000ULL; } while (0);
        func_800D427C(D_800FAF5C, func_800D4D44(D_800FAF5C, 0, D_800F9B0C), 3);
        O->fC++;
        break;
    case 1: {
        s32 s1;
        f32 vec[3];
        f32 buf[3];
        O->flags |= 0x1000000000ULL;
        { s32 h = *(volatile s32 *)&B->f58; s1 = func_800D3684(h, D_800F9B14); }
        if (B->flags & 0x200000) {
            if (s1 < 0) { vec[0] = -90.0f; s1 = 0x400; }
            else { vec[0] = 90.0f; s1 = -0x400; }
            vec[2] = 0.0f;
        } else {
            if (s1 < 0) { vec[0] = -90.0f; s1 = 0x400; }
            else { vec[0] = 90.0f; s1 = -0x400; }
            vec[2] = 10.0f;
        }
        func_800D3E40((u8 *)D_800F9B00 + 0x6C, vec, B->f58, buf);
        func_800D7128(D_800F9B00, D_800FAF5C, buf, D_800FACF8 + D_800FADB8 * 0x30);
        D_800EB520[D_800FADB8] = func_800D35B0(B->f58, s1);
        O->fC++;
    }

    case 2: {
        s32 s0;
        O->flags |= 0x1000000000ULL;
        func_800D2C68(D_800FAF5C, D_800F9B00, 2.0f, D_800FACF8 + D_800FADB8 * 0x30, 2);
        s0 = stepEntityXZQuadraticSpline(D_800FAF5C, D_800FACF8 + D_800FADB8 * 0x30) << 24;
        s0 >>= 24;
        s0 += (s8)func_800A7240(D_800FAF5C, D_800EB520[D_800FADB8], 0x38, 0);
        s0 <<= 16;
        s0 >>= 16;
        if (s0 == 2) {
            if (func_800D3684(B->f58, D_800F9B14) < 0) {
                s0 = (B->flags & 0x200000) ? 0xF4C : 0xF42;
            } else {
                s0 = (B->flags & 0x200000) ? 0xF4A : 0xF44;
            }
            func_800D427C(D_800FAF5C, s0, 2);
            O->f360 |= 1;
            O->fC++;
        }
        break;
    }
    case 3: {
        s16 s0;
        func_800D2BAC(D_800FAF5C, D_800F9B00, 2.0f, 2);
        if (O->f4 > 0) break;
        if (O->f360 & 2) {
            switch (O->f8) {
            case 0xF42: s0 = 0xF53; break;
            case 0xF44: s0 = 0xF55; break;
            case 0xF4A: s0 = 0xF57; break;
            case 0xF4C: s0 = 0xF59; break;
            }
            func_800D427C(D_800FAF5C, s0, 1);
        } else {
            func_800D427C(D_800FAF5C, O->f8 + 4, 0);
        }
        O->fC++;
        break;
    }
    case 4:
        func_800D2BAC(D_800FAF5C, D_800F9B00, 2.0f, 2);
        if (O->f4 > 0) break;
        func_800D4AD0(D_800FAF5C);
        if (O->f8 == 0xF57 || O->f8 == 0xF59) {
            func_800D427C(D_800FAF5C, 0xE8E, 1);
            O->fC++;
        } else {
            if (O->f8 < 0xF53) func_800A6C48(D_800FAF5C, 0x2B);
            else beginEntityActionA8D8C(D_800FAF5C);
            { Nw2F5C *o = O; o->f362 = -1; o->flags &= ~0x40000000ULL; }
        }
        break;
    case 5:
        func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 1), 1);
        break;
    }
}
