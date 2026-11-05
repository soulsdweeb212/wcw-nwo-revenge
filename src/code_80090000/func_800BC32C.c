/* @header
 * func_800BC32C
 * VRAM 0x800BC32C | ROM 0x68A9C | size 0x1E0
 * asm: asm/nonmatchings/code_80090000/func_800BC32C.s
 */
#include "common.h"

extern s32 D_800E74C4, D_800E74D8, D_800E8204, D_800E8200, D_800E79CC, D_800E74F0, D_800E74E0, D_800E798C;
extern s32 D_800E9F90, D_800E9F8C, D_800E7BEC, D_800E7C90, D_800E74E8, D_800E8210, D_80038AA8, D_800D5F28;
extern s32 D_800DF1D8, D_800DF1D4;
extern f32 D_800E7510, D_800E750C, D_800E7508, D_800E7500, D_800E74FC, D_800E74F8;
extern s16 D_8006E440;
extern u8 D_8007EF30[];
void func_800BBEB8(s32);
s32 guRandom(void);
void func_800B807C(s32, s32);
void func_8000DFD0(s32);

void func_800BC32C(void) {
    s32 r;

    D_800E74C4 = 0;
    D_800E74D8 = -5;
    D_800E8204 = -5;
    D_800E8200 = -5;
    D_800E79CC = 0;
    D_800E74F0 = -1;
    D_800E74E0 = 0;
    D_800E798C = 0;
    D_800E9F90 = 0;
    D_800E9F8C = 0;
    D_800E7BEC = 0;
    D_800E74F8 = D_800E74FC = D_800E7500 = D_800E7508 = D_800E750C = D_800E7510 = 0.0f;
    func_800BBEB8(D_800E7C90);
    D_800E74E8 = -1;
    D_800DF1D8 = 0;
    D_800DF1D4 = 0;
    do {
        r = guRandom() % 6;
    } while ((D_800DF1D4 >> r) & 1);
    D_800DF1D4 |= 1 << r;
    func_800B807C(0, r + 1);
    do {
        r = guRandom() % 5;
    } while ((D_800DF1D8 >> r) & 1);
    D_800DF1D8 |= 1 << r;
    D_800E8210 = r;
    D_8006E440 = 1;
    func_8000DFD0(0);
    if ((*(u16 *)(D_8007EF30 + 8) & 0x8000) && D_80038AA8 == 8) {
        D_800D5F28 = 0xC0;
    }
}
