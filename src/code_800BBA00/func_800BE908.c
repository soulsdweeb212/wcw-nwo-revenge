#include "common.h"

typedef struct { s32 f0; s16 f4; s16 f6; s16 f8; s16 fA; s16 fC; s16 fE; u8 pad10[0x48]; s32 f58; } Nw2F5C;
typedef struct { u8 pad0[8]; u16 f8; u8 padA[0x356]; u16 f360; } Nw2F9B00;
extern void *D_800FAF5C;
extern void *D_800F9B00;
void func_800D427C(void *, s16, s32);
s32 func_800D35B0(s32, s32);
s8 func_800BF150(void *);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800C472C(void *, void *, s32);
#define A ((Nw2F5C *) D_800FAF5C)
#define B ((Nw2F9B00 *) D_800F9B00)
void func_800BE908(void)
{
    s32 x;
    switch (A->fC) {
    case 0:
        func_800D427C(A, (s16)(B->f8 + 1), 3);
        A->fC++;
        break;
    case 1:
        if (A->f4 <= 0) {
            A->f58 = func_800D35B0(A->f58, (B->f360 & 1) ? -0x400 : 0x400);
            func_800D427C(A, (s16)(B->f8 + 1), 1);
            A->fC++;
        }
        break;
    case 2:
        x = (s32)D_800F9B00;
        if (((Nw2F9B00 *)x)->f360 & 2) {
            x = ((Nw2F9B00 *)x)->f8;
            func_800D427C(A, (s16)(x + 1), 3);
            A->fC++;
        } else if (((Nw2F9B00 *)x)->f360 & 4) {
            x = ((Nw2F9B00 *)x)->f8;
            func_800D427C(A, (s16)(x + 1), 3);
            A->fC += 2;
        } else if (func_800BF150(A)) {
            B->f360 |= 4;
        }
        break;
    case 3:
        if (A->f4 <= 0) {
            func_800A7D1C(A, (A->fA == 0xE) ? 0x27 : 0x28);
            func_800B68A0(A, B, A);
            func_800D4AD0(A);
            beginEntityActionA8D8C(A);
            func_800C472C(A, A, 2);
        }
        break;
    case 4:
        if (A->f4 <= 0) {
            func_800D4AD0(A);
            func_800A6C48(A, 0x2B);
        }
        break;
    }
}
