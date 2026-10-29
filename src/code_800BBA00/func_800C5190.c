#include "common.h"

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    s16 fC;
    u8 padE[0x12];
    u64 flags;
} Nw2Act5190;

extern Nw2Act5190 *D_800FAF5C;
extern s8 D_800FADB8;
extern u32 D_800FABD8;
extern u32 D_800E3F20[];
extern u8 D_800F9D10[];

void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
void func_800D427C(void *, s16, s32);
void func_800A7F6C(void *, s32);
s8 func_800C2CDC(void *, s16);
void func_800C3A78(void *, void *, s32);
void func_800D25D0(void *, f32);
s32 func_800D2B64(void *, f32, u16, s32);
void func_800A7188(void *);

void func_800C5190(void) {
    Nw2Act5190 *o;
    s16 snd;
    s16 eff;
    s32 flag;
    s8 ent;
    f32 two;

    o = D_800FAF5C;
    switch (o->fC) {
    case 0:
        switch (o->fA) {
        case 0x1B:
            snd = 0xB5;
            break;
        case 0x1C:
            snd = 0xB6;
            break;
        case 0x1D:
            if (o->flags & 0x8000000000ULL) {
                snd = 0xB8;
            } else {
                snd = 0xB7;
            }
            break;
        }
        func_800A7C40(D_800FAF5C, D_800FADB8, snd);
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 2);
        func_800A7F6C(D_800FAF5C, 0);
        D_800FAF5C->fC++;
    case 1:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        switch (D_800FAF5C->fA) {
        case 0x1B:
            eff = 0x11;
            break;
        case 0x1C:
            eff = 0x13;
            break;
        case 0x1D:
            eff = 0x12;
            break;
        }
        ent = func_800C2CDC(D_800FAF5C, eff);
        if (ent != -1) {
            D_800FAF5C->fC++;
            switch (D_800FAF5C->fA) {
            case 0x1B:
                flag = 0x20;
                break;
            case 0x1C:
                flag = 0x40;
                break;
            case 0x1D:
                flag = 0x80;
                break;
            }
            func_800C3A78(D_800FAF5C, &D_800F9D10[ent * 0x3B0], flag);
        }
    case 2:
        two = 2.0f;
        func_800D25D0(D_800FAF5C, two);
        func_800D2B64(D_800FAF5C, two, 0, 0xE);
        func_800A7188(D_800FAF5C);
        break;
    }
}
