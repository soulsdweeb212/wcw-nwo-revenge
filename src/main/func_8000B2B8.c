#include "common.h"

extern s8 D_800485B0[4][8];
extern s8 D_800485D0[4][8];
void setIndexedS16Pair(s32, s32, s8, s8);

/* Flush every active slot pair for player arg0: forward its two bytes to
 * setIndexedS16Pair and mark the slot empty. */
void func_8000B2B8(s32 arg0) {
    s32 i = 0;
    s32 a0 = (s16)arg0;

    for (i = 0; i < 8U; i++) {
        if (D_800485B0[a0][(s16)i] >= 0) {
            setIndexedS16Pair(a0, 0, D_800485D0[a0][(s16)i], D_800485B0[a0][(s16)i]);
            D_800485B0[a0][(s16)i] = -1;
        }
    }
}
