/* @header
 * func_80002C0C
 * VRAM 0x80002C0C | ROM 0x380C | size 0x4C
 * asm: asm/nonmatchings/main/func_80002C0C.s
 */
#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK func_8001C990(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_8001CAC0(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_800467C0;
extern M2C_UNK D_800467E0;
extern s32 D_800467FC;
extern s32 D_80046800;

/* Resets the two event counters and clears both message queues. */
void func_80002C0C(void) {
    D_800467FC = 0;
    D_80046800 = 0;
    func_8001CAC0(&D_800467C0, 0, 1);
    func_8001C990(&D_800467E0, 0, 1);
}
