#include "common.h"

s32 func_8001C990(s32 *, s32, s32);
extern s32 D_800482F0;
extern s8 D_800484F2;

/* Wait on the message queue D_800482F0, then set the ready flag and return the
 * queue. */
s32 *func_8000424C(void) {
    func_8001C990(&D_800482F0, 0, 1);
    D_800484F2 = 1;
    return &D_800482F0;
}
