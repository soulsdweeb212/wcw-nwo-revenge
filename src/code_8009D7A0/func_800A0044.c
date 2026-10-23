#include "common.h"

/* func_800A0044: two-phase action state machine for the entity in D_800EB408.
 * Phase 0 copies the boundary vectors for the current quadrant
 * (f3E) out of D_800E3C70/D_800E3C74, requests action 0xF02 and, if the
 * animation 0x155 can start, selects sub-action 0x4D and advances. Phase 1,
 * once the phase timer expires, plays animation 0xC, runs the paired action,
 * writes the quadrant heading (D_800E3CC0) and switches to action 0x2B. */
typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s32 f8;
    s16 fC;
    s16 fE;
    u8 pad10[0x2E];
    s16 f3E;
    u8 pad40[0xC];
    f32 f4C;
    u8 pad50[4];
    f32 f54;
    s32 f58;
} Nw2ActionA0044;

extern void *D_800EB408;
extern f32 D_800E3C70[];
extern f32 D_800E3C74[];
extern s32 D_800E3CB0[];
extern s32 D_800E3CC0[];

void func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s32, s32);
s8 func_800A7240(void *, s32, s32, u64);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
void func_800A6C48(void *, s32);

void func_800A0044(void) {
    func_800D2B64(D_800EB408, 2.0f, 0, 2);

    switch (((Nw2ActionA0044 *)D_800EB408)->fC) {
    case 0:
        ((Nw2ActionA0044 *)D_800EB408)->f4C = D_800E3C70[((Nw2ActionA0044 *)D_800EB408)->f3E * 2];
        ((Nw2ActionA0044 *)D_800EB408)->f54 = D_800E3C74[((Nw2ActionA0044 *)D_800EB408)->f3E * 2];
        func_800D427C(D_800EB408, 0xF02, 0);
        if (func_800A7240(D_800EB408, D_800E3CB0[((Nw2ActionA0044 *)D_800EB408)->f3E], 0x155, 0) != 0) {
            func_800A7F6C(D_800EB408, 0x4D);
            func_800A837C(D_800EB408);
            ((Nw2ActionA0044 *)D_800EB408)->fC++;
        }
        break;
    case 1:
        if (((Nw2ActionA0044 *)D_800EB408)->f4 <= 0) {
            func_800A7D1C(D_800EB408, 0xC);
            func_800B68A0(D_800EB408, D_800EB408, D_800EB408);
            ((Nw2ActionA0044 *)D_800EB408)->f58 = D_800E3CC0[((Nw2ActionA0044 *)D_800EB408)->f3E];
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
