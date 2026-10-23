#include "common.h"

extern u8 D_8003A380[];
s32 func_8002B528(s32 arg0);

u8 func_8002B5AC(s32 arg0);

/* Scans the D_8003A380 byte list for the position of the value produced by
 * func_8002B5AC(arg0), then returns the paired entry's id (or 0). */
s32 func_8002B4AC(s32 arg0) {
    s32 i;

    func_8002B5AC(arg0);
    i = 0;
    if (D_8003A380[i] == 0) {
        return 0;
    }
    for (; D_8003A380[i] != 0; i++) {
        if (D_8003A380[i] == i) {
            break;
        }
    }
    if (D_8003A380[i] != 0) {
        return func_8002B528(D_8003A380[i ^ 1]);
    }
    return 0;
}
