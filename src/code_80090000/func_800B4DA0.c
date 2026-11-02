/* @header
 * func_800B4DA0
 * VRAM 0x800B4DA0 | ROM 0x61510 | size 0x78
 * asm: asm/nonmatchings/code_80090000/func_800B4DA0.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern u16 D_800E9962;
extern s32 D_800E79A0, D_800E79A4;
void func_8002B7E0(s32, s32);
void func_800B1D04(s32);
#define F(t, o, i) (*(t *)(D_8007EF30 + (o) + ((i) << 4)))

s32 func_800B4DA0(s32 a) {
    s32 r, s;
    func_8002B7E0(F(s16, 0x4E, D_800E9962), F(u8, 0x50, D_800E9962));
    if (a == 0x422) {
        func_800B1D04(2);
        r = 0x12;
        s = 0xF;
    } else {
        func_800B1D04(3);
        r = 0x12;
        s = 0xF;
    }
    D_800E79A0 = s;
    D_800E79A4 = 0;
    return r;
}
