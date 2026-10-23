#include "common.h"

/* Action selector for self D_800FABD0:
 * phase 0: pick a direction from the opponent's position (with a random
 *          +/-2 jitter) and store the next action id;
 * phase 1: when the opponent's state matches, either start the wind-up action
 *          (with a probability check) or clear back to idle; always re-sync
 *          the stored opponent state. */
typedef struct {
    u8 pad0[2];
    s16 f2;
    s16 f4;
    s16 f6;
    u8 pad8[2];
    u16 fA;
    u8 padC[6];
    s16 f12;
    u8 pad14[0x1A];
    s16 f2E;
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x24];
    u32 flags5C;
} Nw2B44Action;

typedef struct {
    u8 pad0[6];
    u16 f6;
    u8 pad8[2];
    s16 fA;
    u8 padC[0x4C];
    void *f58;
} Nw2B44State;

extern Nw2B44Action *D_800FABD0;
extern Nw2B44State *D_800F9B60;
extern u8 *D_800FAF58;
extern u16 D_800E3CF0[];
extern f64 D_800E5480;
extern f64 D_800E5488;

s32 func_800D3638(void *);
s8 func_800D4198(s16);

void func_800B44B8(void) {
    s16 phase = D_800FABD0->f4;

    switch (phase) {
    case 0: {
        s32 dirIndex = func_800D3638(D_800F9B60->f58);
        if (func_800D4198(0x1F4) != 0) {
            dirIndex += 2;
        } else {
            dirIndex -= 2;
        }
        D_800FABD0->fA = D_800E3CF0[dirIndex & 7];
        D_800FABD0->f4++;
        break;
    }
    case 1:
        if (((Nw2B44State *)D_800FAF58)->fA == phase) {
            if (D_800FABD0->f34 < D_800E5480
                && func_800D4198(func_800D4198((s16)((f64)D_800FABD0->f12 * D_800E5488))) != 0) {
                D_800FABD0->f2 = 0x20;
                D_800FABD0->f4 = 0;
                D_800FABD0->f2E = D_800F9B60->fA;
                D_800FABD0->flags5C &= ~7;
                return;
            }
            D_800FABD0->f6 = D_800FABD0->fA;
        } else {
            D_800FABD0->f2 = 0;
            D_800FABD0->f4 = 0;
            D_800FABD0->f2E = D_800F9B60->fA;
            D_800FABD0->flags5C &= ~7;
        }
        if (D_800FABD0->f2E != D_800F9B60->fA) {
            D_800FABD0->f2 = 0;
            D_800FABD0->f4 = 0;
            D_800FABD0->f2E = D_800F9B60->fA;
            D_800FABD0->flags5C &= ~7;
        }
        break;
    }
}
