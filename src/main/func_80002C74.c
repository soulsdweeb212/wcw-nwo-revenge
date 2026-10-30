/* @header
 * func_80002C74
 * VRAM 0x80002C74 | ROM 0x3874 | size 0x50
 * asm: asm/nonmatchings/main/func_80002C74.s
 */
#include "common.h"

s32 func_8001C990(s32 *, s32, s32);
s32 func_8001CAC0(s32 *, s32, s32);
extern s32 D_800467C0;
extern s32 D_800467E0;
extern s32 D_800467FC;
extern s32 D_80046800;

/* Initialize two message queues (D_800467C0, D_800467E0), mark the second active,
 * and post a zero message to each. */
void func_80002C74(void) {
    D_800467FC = 0;
    D_80046800 = 1;
    func_8001CAC0(&D_800467C0, 0, 1);
    func_8001C990(&D_800467E0, 0, 1);
}
