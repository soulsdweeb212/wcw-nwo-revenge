#include "common.h"

s32 func_80013CA4(s32, s32);
extern s32 D_80036738;

/* Release the pending audio resource at level 0x1E and clear the pointer. */
void func_8000E09C(void) {
    if (D_80036738 != 0) {
        func_80013CA4(D_80036738, 0x1E);
        D_80036738 = 0;
    }
}
