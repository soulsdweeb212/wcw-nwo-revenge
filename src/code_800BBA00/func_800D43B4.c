/* @header
 * func_800D43B4
 * VRAM 0x800D43B4 | ROM 0xC7854 | size 0x28
 * asm: asm/nonmatchings/code_800BBA00/func_800D43B4.s
 */
#include "common.h"

extern s32 gRandSeed;
extern s32 D_800EB634;
extern u16 D_800EB638[];

s32 func_8001C580(void);
void func_800D427C(void *, s32);

/* Reset the entity's s16 +8 state to -1, then invoke func_800D427C. */
void func_800D43B4(void *entity, s16 action) {
    *(s16 *)((u8 *)entity + 8) = -1;
    func_800D427C(entity, action);
}
