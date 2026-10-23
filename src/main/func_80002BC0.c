#include "common.h"

s32 func_8001C990(s32 *, s32, s32);
s32 func_8001CAC0(s32 *, s32, s32);
extern s32 D_800467C0;
extern s32 D_800467E0;
extern s32 D_800467FC;
extern s32 D_80046800;

/* Set the queue's mode from arg0, clear the active flag, and post a zero message to
 * both message queues (D_800467C0, D_800467E0). */
void func_80002BC0(s32 arg0) {
    D_800467FC = arg0;
    D_80046800 = 0;
    func_8001CAC0(&D_800467C0, 0, 1);
    func_8001C990(&D_800467E0, 0, 1);
}
