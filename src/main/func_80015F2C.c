#include "common.h"

/* Adds arg1 to each of the arg2 non-zero s32 entries starting at arg0. */
void func_80015F2C(s32 *arg0, s32 arg1, u32 arg2) {
    volatile u64 pad;
    u32 i = 0;

    if (arg2 != 0) {
        do {
            i++;
            if (*arg0 != 0) {
                *arg0 += arg1;
            }
            arg0++;
        } while (i < arg2);
    }
}
