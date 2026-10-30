/* @header
 * func_80096A20
 * VRAM 0x80096A20 | ROM 0x43190 | size 0x28
 * asm: asm/nonmatchings/code_80090000/func_80096A20.s
 */
#include "common.h"

extern u8 updateActionStateC5D48[];

extern u8 applyMovementToEntityPair[];
void func_800948BC(s32);
s32 func_80090384(s32, s32, s32);

s32 func_80002C58(void);
s32 func_80002C74(void);
s32 func_8000E55C(s32, s32, s32);
s32 func_800C4D70(void);
s32 func_800C5010(void);
s32 func_800C51A0(void);
s32 func_800C594C(void);
extern u8 func_800D6658[];

extern s16 D_800E6B78;
extern s16 D_800E821C;

/* Set the two global s16 options from the arguments, ignoring a negative
 * argument (leaving the existing value in place). */
void func_80096A20(s32 a, s32 b) {
    if (a >= 0) {
        D_800E821C = a;
    }
    if (b >= 0) {
        D_800E6B78 = b;
    }
}
