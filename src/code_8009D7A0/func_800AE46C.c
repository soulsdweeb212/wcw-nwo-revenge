#include "common.h"

extern u8 *D_800F9B60;
extern u8 *D_800FAF58;
extern f64 D_800E51C8;
s8 func_800D4198(s16);

typedef struct {
    u8 pad0[2];
    s16 f2;
    s16 f4;
    u16 f6;
    u8 pad8[0xA];
    s16 f12;
    s16 f14;
    u8 pad16[0xC];
    s16 f22;
    u8 pad24[0xA];
    u16 f2E;
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x24];
    u32 f5C;
} Nw2ActionABD0;
extern Nw2ActionABD0 *D_800FABD0;

void func_800AE46C(void) {
    s16 state = D_800FABD0->f4;
    switch (state) {
    case 0:
        D_800FABD0->f6 = 0x4000;
        if (func_800D4198(0x1F4) != 0) {
            D_800FABD0->f6 = 0x4F00;
        }
        D_800FABD0->f4 = D_800FABD0->f4 + 1;
        break;
    case 1:
        if (*(s16 *)(D_800FAF58 + 0xA) == 0x1E) {
            D_800FABD0->f4 = state + 1;
        } else {
            u8 *g = D_800F9B60;
            u32 flags = D_800FABD0->f5C;
            D_800FABD0->f2 = 0;
            D_800FABD0->f4 = 0;
            {
                u16 value = *(u16 *)(g + 0xA);
                D_800FABD0->f5C = flags & ~7;
                D_800FABD0->f2E = value;
            }
        }
        break;
    case 2: {
        s16 mode = *(s16 *)(D_800FAF58 + 0xA);
        u16 value;
        Nw2ActionABD0 *p;
        if (mode == 0x1E) break;
        if (mode >= 0x1F) break;
        if (mode != 1) break;
        if ((f64)D_800FABD0->f34 < D_800E51C8) {
            if (func_800D4198(D_800FABD0->f12) != 0 && func_800D4198(0xFA) != 0) {
                D_800FABD0->f4 = 0;
                break;
            }
            if (func_800D4198(D_800FABD0->f12) != 0) {
                u8 *g = D_800F9B60;
                s16 mode2 = *(s16 *)(g + 0xA);
                if (mode2 == 1) {
                    p = D_800FABD0;
                    p->f2 = 1;
                    p->f4 = 0;
                    value = *(u16 *)(g + 0xA);
                    goto update;
                }
                if (mode2 == 0x40) {
                    p = D_800FABD0;
                    p->f2 = 1;
                    p->f4 = 0;
                    value = *(u16 *)(g + 0xA);
                    goto update;
                }
                switch (D_800FABD0->f22) {
                case 6:
                    D_800FABD0->f6 = 0x10;
                    break;
                case 10:
                    if (func_800D4198(0x1F4) != 0) {
                        D_800FABD0->f6 = 0x8000;
                    } else {
                        D_800FABD0->f6 = 0x20;
                    }
                    break;
                }
            }
        }
        p = D_800FABD0;
        p->f2 = 0;
        p->f4 = 0;
        value = *(u16 *)(D_800F9B60 + 0xA);
update:
        p->f2E = value;
        p->f5C &= ~7;
        break;
    }
    }
}
