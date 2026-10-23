#include "common.h"

typedef struct {
    s16 f0, f2, f4, f6, f8, fA;
    u8 padC[0x14];
    u64 f20;
    u8 pad28[6];
    u16 f2E;
    u8 pad30[0x1C];
    f32 f4C, f50, f54;
    u8 pad58[4];
    u32 f5C;
    u8 pad60[0xC];
    f32 pos[3];
} B51Obj;
extern B51Obj *D_800FABD0, *D_800FAF58, *D_800F9B60;
extern u16 D_800E3CF0[];
extern u8 D_8007E228[], D_8007EF30[];
s32 func_800D36E8(f32, f32);
s32 func_800D3614(s32);
s8 func_800D4198(s16);

#define REG280 (*(u16 *)(D_8007E228 + 0x58))
#define REG0A0 (*(u16 *)(D_8007EF30 + 0x170))

void func_800B0518(void) {
    s16 state;

    switch (D_800FABD0->f4) {
    case 0:
        D_800FABD0->f8 = 8;
        D_800FABD0->f6 = D_800E3CF0[(s16)func_800D3614(func_800D36E8(D_800FAF58->f4C, D_800FAF58->f54))];
        state = D_800FAF58->fA;
        if (state != 1) {
            if (state == 0x61) {
                D_800FABD0->f4++;
            } else {
                B51Obj *g = D_800F9B60;
                u16 oldState;
                D_800FABD0->f2 = 0;
                D_800FABD0->f4 = 0;
                oldState = g->fA;
                D_800FABD0->f5C &= ~7;
                D_800FABD0->f2E = oldState;
            }
        } else if (!(!(REG280 & 0x200) || (REG0A0 & 0x40) ||
                     (D_800FAF58->f20 & 0x200ULL) ||
                     !(D_800FAF58->f20 & 0x80ULL))) {
            B51Obj *g = D_800F9B60;
            u16 oldState;
            D_800FABD0->f2 = 0;
            D_800FABD0->f4 = 0;
            oldState = g->fA;
            D_800FABD0->f5C &= ~7;
            D_800FABD0->f2E = oldState;
        }
        if (!(D_800FAF58->f20 & 0x8000ULL)) return;
        break;
    case 1:
        if (func_800D4198(500)) D_800FABD0->f6 = 8;
        if (D_800FAF58->fA == 0x61) return;
        break;
    default:
        return;
    }
    {
        B51Obj *g = D_800F9B60;
        D_800FABD0->f2 = 0;
        D_800FABD0->f4 = 0;
        D_800FABD0->f2E = g->fA;
        D_800FABD0->f5C &= ~7;
    }
}
