#include "common.h"

s32 func_8001CAC0(s32 *, s32, s32);
extern s32 D_80073E98;

/* Send a zero message to the queue at D_80073E98. */
void func_80027FC0(void) {
    func_8001CAC0(&D_80073E98, 0, 0);
}
