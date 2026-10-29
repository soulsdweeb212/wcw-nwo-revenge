#include "common.h"

s32 func_800D2B64(void *, f32, u16, s32);
void func_800D93DC(void *);
void func_800D427C(void *, s32, s32);
void func_800A6C48(void *, s32);

void func_8009F774(void) {
    func_800D2B64(D_800EB408, 2.0f, 0, 0xFFFFE);
    func_800D93DC(D_800EB408);
    switch (((Nw2F408 *)D_800EB408)->fC) {
    case 0:
        func_800D427C(D_800EB408, 0x109D, 2);
        ((Nw2F408 *)D_800EB408)->fC++;
        break;
    case 1:
        if (((Nw2F408 *)D_800EB408)->f4 <= 0) {
            func_800A6C48(D_800EB408, 1);
        }
        break;
    }
}
