#include "common.h"

typedef struct {
    s16 f0, f2, f4, f6;
    u16 f8;
    s16 fA;
    u8 padC[8];
    s16 f14;
    u8 pad16[0xA];
    u64 flags;
    u8 pad28[6];
    u16 f2E;
    u8 pad30[0x2C];
    u32 f5C;
    u8 pad60[0xC];
    f32 pos[3];
} B08Obj;

extern B08Obj *D_800FABD0, *D_800FAF58, *D_800F9B60;
extern u16 D_800E3CF0[];
s32 func_800D3650(void *, void *);

void func_800B0830(void) {
    s16 state;
    u16 anim;
    switch (D_800FABD0->f4) {
    case 0:
        anim = D_800E3CF0[(s16)func_800D3650(D_800FAF58->pos, D_800F9B60->pos)];
        D_800FABD0->f6 = anim;
        D_800FABD0->f8 = 0x8000;
        state = D_800FAF58->fA;
        if (state == 0x64) {
            D_800FABD0->f4++;
            return;
        }
        if (D_800FABD0->f14 == 1) {
            if (!(D_800FAF58->flags & 0x40) || !(D_800F9B60->flags & 0x100)) {
                D_800FABD0->f2 = 0;
                D_800FABD0->f4 = 0;
                D_800FABD0->f2E = D_800F9B60->fA;
                D_800FABD0->f5C &= ~7;
            }
        } else {
            B08Obj *g = D_800F9B60;
            u16 oldState;
            D_800FABD0->f2 = 0;
            D_800FABD0->f4 = 0;
            oldState = g->fA;
            D_800FABD0->f5C &= ~7;
            D_800FABD0->f2E = oldState;
        }
        return;
    case 1:
        state = D_800FAF58->fA;
        if (state != 0x64) {
            B08Obj *g = D_800F9B60;
            u16 oldState;
            D_800FABD0->f2 = 0;
            D_800FABD0->f4 = 0;
            oldState = g->fA;
            D_800FABD0->f5C &= ~7;
            D_800FABD0->f2E = oldState;
        }
        break;
    }
}
