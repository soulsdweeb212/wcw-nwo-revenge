/* @header
 * func_800033C0
 * VRAM 0x800033C0 | ROM 0x3FC0 | size 0x38
 * asm: asm/nonmatchings/main/func_800033C0.s
 */
#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK func_80013CA4(s32, s16);
extern s32 D_8002EED0;

/* Applies arg0 to the pending sound handle and clears it. */
void func_800033C0(s16 arg0) {
    if (D_8002EED0 != 0) {
        func_80013CA4(D_8002EED0, arg0);
        D_8002EED0 = 0;
    }
}
