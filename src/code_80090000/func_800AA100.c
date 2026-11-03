/* @header
 * func_800AA100
 * VRAM 0x800AA100 | ROM 0x56870 | size 0xE0
 * asm: asm/nonmatchings/code_80090000/func_800AA100.s
 */
#include "common.h"

extern struct { u8 pad0[8]; u16 mode; } D_8007EF30;
extern struct { u8 pad0[0x620]; s32 f620; } D_8007E228;

s32 func_800AA100(s32 a) {
    if (D_8007EF30.mode & 0x60) {
        if (D_8007E228.f620 & 0x200) {
            return (a == 0 || a == 1) ? 1 : 2;
        }
        if (D_8007E228.f620 & 0x100) {
            return (a == 2 || a == 3) ? 1 : 2;
        }
        return 3;
    }
    if (D_8007E228.f620 & 1) {
        return a == 0 ? 1 : 2;
    }
    if (D_8007E228.f620 & 2) {
        return a == 1 ? 1 : 2;
    }
    if (D_8007EF30.mode & 0x80) {
        if (D_8007E228.f620 & 4) {
            return a == 2 ? 1 : 2;
        }
        if (D_8007E228.f620 & 8) {
            return a == 3 ? 1 : 2;
        }
    }
    return 3;
}
