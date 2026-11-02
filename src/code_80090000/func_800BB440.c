/* @header
 * func_800BB440
 * VRAM 0x800BB440 | ROM 0x67BB0 | size 0x164
 * asm: asm/nonmatchings/code_80090000/func_800BB440.s
 */
#include "common.h"

extern u16 D_800EA0C2;
extern s32 D_800DF1D0, D_800DF1C0, D_800DF1CC, D_800E7C90;
void findOrAddCacheEntryRaw(s32, s32, s32, s32, s32);
void func_800BB110(void);

void func_800BB440(void) {
    s32 r;
    findOrAddCacheEntryRaw(0x119, 0xF0, 0x64, 8, 0x420);
    r = 0;
    D_800DF1D0 = 1;
    if (D_800EA0C2 & 0xC00) {
        D_800DF1CC = 0x409;
        D_800DF1C0 ^= 1;
    } else if (D_800EA0C2 & 0x8000) {
        r = D_800DF1C0 ? -1 : 1;
    } else if (D_800EA0C2 & 0x4000) {
        if (D_800DF1C0 == 0) {
            D_800DF1C0 = 1;
            D_800DF1CC = 0x409;
        } else {
            r = -1;
        }
    }
    findOrAddCacheEntryRaw(0x11E, 0xE0, 0x8C, 8, 0x20);
    findOrAddCacheEntryRaw(0x11F, 0xE0, D_800DF1C0 * 14 + 0x8C, 8, 0x121);
    switch (r) {
    case 1:
        D_800DF1CC = 0x429;
        func_800BB110();
        D_800E7C90 = 0x31;
        break;
    case -1:
        D_800DF1CC = 0x403;
        D_800E7C90 = 0x31;
        break;
    }
}
