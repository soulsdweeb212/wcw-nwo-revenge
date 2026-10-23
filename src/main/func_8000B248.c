#include "common.h"

extern s8 D_800485B0[4][8];
extern s8 D_800485D0[4][8];
void setIndexedS16Pair(s32, s32, s8, s8);

/* Releases the pending indexed pair at (arg0,arg1): writes the stored pair and
 * marks the slot free (-1). */
void func_8000B248(s32 arg0, s32 arg1) {
    s32 a0 = (s16)arg0;

    if (D_800485B0[a0][(s16)arg1] >= 0) {
        setIndexedS16Pair(a0, 0, D_800485D0[a0][(s16)arg1], D_800485B0[a0][(s16)arg1]);
        D_800485B0[a0][(s16)arg1] = -1;
    }
}
