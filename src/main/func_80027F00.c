#include "common.h"

s32 func_8001C890(s32 *, s32 *, s32);
s32 func_8001CAC0(s32 *, s32, s32);
extern s32 D_800389A0;
extern s32 D_80064AC0;
extern s32 D_80073E98;

/* Initialize the message queue at D_80073E98 from D_80064AC0, mark it active, and
 * send a zero message. */
void func_80027F00(void) {
    D_800389A0 = 1;
    func_8001C890(&D_80073E98, &D_80064AC0, 1);
    func_8001CAC0(&D_80073E98, 0, 0);
}
