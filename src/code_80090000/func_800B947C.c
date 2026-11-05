/* @header
 * func_800B947C
 * VRAM 0x800B947C | ROM 0x65BEC | size 0x1C4
 * asm: asm/nonmatchings/code_80090000/func_800B947C.s
 */
#include "common.h"

extern u8 D_80038AB0;
extern s32 D_800EA218, D_800DCFBC, D_800DCFC4, D_800DCFC0;
extern u8 D_800DCF50[], D_800D2938[], D_800D2948[];

static inline s32 mount(void) {
    u8 b[0x68];

    D_800DCFBC = osPfsInitPak(D_800DCFC4, D_800DCF50, 0);
    if (D_800DCFBC == 0xA) {
        if (osMotorInit(D_800DCFC4, b, 0) == 0) {
            D_800DCFBC = 0x40;
        }
        D_80038AB0 = 0;
    }
    return D_800DCFBC;
}

s32 func_800B947C(void) {
    D_800EA218 = 0;
    if (D_80038AB0 == 0) {
        D_800DCFBC = mount();
        if (D_800DCFBC != 0) {
            return D_800DCFBC;
        }
        D_80038AB0 = 1;
    }
    D_800DCFBC = osPfsFindFile(D_800DCF50, 0x4538, 0x4E56504A, D_800D2938, D_800D2948, &D_800DCFC0);
    if (D_800DCFBC == 2) {
        D_80038AB0 = 0;
        D_800EA218 |= 1;
        D_800DCFBC = mount();
        if (D_800DCFBC == 0) {
            D_80038AB0 = 1;
            D_800DCFBC = osPfsFindFile(D_800DCF50, 0x4538, 0x4E56504A, D_800D2938, D_800D2948, &D_800DCFC0);
        }
    }
    return D_800DCFBC;
}
