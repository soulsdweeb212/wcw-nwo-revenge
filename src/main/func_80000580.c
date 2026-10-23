#include "common.h"

void func_80000D28(void *, s32, s32);
extern s32 D_8003DE30;

/* Push a message (arg0, arg1) onto the event list at D_8003DE30. */
void func_80000580(s32 arg0, s32 arg1) {
    func_80000D28(&D_8003DE30, arg0, arg1);
}
