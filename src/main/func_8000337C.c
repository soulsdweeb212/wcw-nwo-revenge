/* @header
 * func_8000337C
 * VRAM 0x8000337C | ROM 0x3F7C | size 0x44
 * asm: asm/nonmatchings/main/func_8000337C.s
 */
#include "common.h"

void func_800033C0(s32);
s32 func_8001381C(s32);
extern s32 D_8002EED0;

/* When arg0 is nonzero, reset the current track and load the new one; return the
 * current track id. */
s32 func_8000337C(s32 arg0) {
    if (arg0 != 0) {
        func_800033C0(0);
        D_8002EED0 = func_8001381C(arg0);
    }
    return D_8002EED0;
}
