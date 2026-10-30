/* @header
 * func_800B31F0
 * VRAM 0x800B31F0 | ROM 0xA6690 | size 0x4B8
 * asm: asm/nonmatchings/code_8009D7A0/func_800B31F0.s
 */
#include "common.h"

typedef struct {
    u8 pad0[2];
    s16 f2;
    s16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
    s8 fC;
    u8 padD[0x11];
    s16 f1E;
    u8 pad20[2];
    s16 f22;
    u8 pad24[4];
    s16 f28;
    u8 pad2A[2];
    s16 f2C;
    u16 f2E;
    u8 pad30[0x2C];
    u32 f5C;
} Nw2B31Action;

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 pad1[0x14];
    u64 flags;
    u8 pad2[0x44];
    f32 f6C;
    u8 pad3[4];
    f32 f74;
} Nw2B31Obj;

extern Nw2B31Action *D_800FABD0;
extern Nw2B31Obj *D_800FAF58;
extern Nw2B31Obj *D_800F9B60;
extern u16 D_800E3CD0[];
extern u16 D_800E3CD8[];
s8 func_800D4198(s16);
f32 func_800D3564(f32);

void func_800B31F0(void)
{
    Nw2B31Obj *o;
    f32 d;

    switch (D_800FABD0->f4) {
    case 0:
        if (D_800FAF58->flags & 0xC0) {
            if (func_800D4198(D_800FABD0->f28 * 10)) {
                if (D_800FAF58->flags & 0x80) {
                    D_800FABD0->f4 = 2;
                    return;
                }
                {
                    u16 t = D_800E3CD0[D_800FABD0->f2C] | 0xC;
                    D_800FABD0->f4++;
                    D_800FABD0->fA = t;
                    D_800FABD0->f6 = t;
                }
                return;
            }
        }
        break;
    case 1:
        o = D_800FAF58;
        switch (o->fA) {
        case 0x2B:
        case 0x60:
        case 0x86:
            return;
        case 4:
            D_800FABD0->f4 = 5;
            return;
        case 3:
        case 0x89:
        case 0x8A:
            D_800FABD0->f6 = D_800FABD0->fA;
            return;
        case 1:
            if (o->flags & 0x80) {
                D_800FABD0->f4++;
                return;
            }
            break;
        }
        break;
    case 2:
        if (!(D_800FAF58->flags & 0x80)) {
            break;
        }
        if (!(D_800F9B60->flags & 0x40)) {
            break;
        }
        switch (D_800FABD0->f1E) {
        case 0:
        case 2:
            d = D_800F9B60->f6C - D_800FAF58->f6C;
            if (d < 0.0) {
                D_800FABD0->f6 = 0x200;
            } else {
                D_800FABD0->f6 = 0x100;
            }
            break;
        case 1:
        case 3:
            d = D_800F9B60->f74 - D_800FAF58->f74;
            if (d < 0.0) {
                D_800FABD0->f6 = 0x400;
            } else {
                D_800FABD0->f6 = 0x800;
            }
            break;
        }
        if (!(func_800D3564(d) < 15.0)) {
            return;
        }
        switch (D_800FABD0->f22) {
        case 6:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            D_800FABD0->f4++;
            return;
        }
        if (D_800F9B60->flags & 0x1000000000ULL) {
            D_800FABD0->f6 = 0;
            return;
        }
        if (func_800D4198(500)) {
            D_800FABD0->f4++;
            return;
        }
        break;
    case 3:
        {
            u16 t = D_800E3CD8[D_800FABD0->f1E];
            D_800FABD0->f8 = 0x8000;
            D_800FABD0->f4++;
            D_800FABD0->f6 = t;
        }
        return;
    case 4:
        if (D_800FAF58->fA == 0x69) {
            return;
        }
        break;
    case 5:
        if (D_800FAF58->fA == 3) {
            D_800FABD0->f8 = 0xF00;
            return;
        }
        if (D_800FAF58->fA == 4) {
            return;
        }
        break;
    default:
        return;
    }
    D_800FABD0->f2 = 0;
    D_800FABD0->f4 = 0;
    D_800FABD0->f2E = D_800F9B60->fA;
    D_800FABD0->f5C &= ~7;
}
