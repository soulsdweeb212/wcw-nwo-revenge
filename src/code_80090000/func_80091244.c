/* @header
 * func_80091244
 * VRAM 0x80091244 | ROM 0x3D9B4 | size 0x28
 * asm: asm/nonmatchings/code_80090000/func_80091244.s
 */
#include "common.h"

extern u8 updateActionStateC5D48[];

/* Emits a display-list pointer to updateActionStateC5D48+0x48 into the command
 * buffer and advances the cursor. */
void func_80091244(u32 **arg0) {
    u32 *p = *arg0;
    u32 *start = p;
    p += 2;
    start[0] = 0xDE000000;
    start[1] = (u32)updateActionStateC5D48 + 0x48;
    *arg0 = p;
}

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

typedef struct {
    u8 pad[0x6D8];
    volatile s32 flag;
} S800D6658;
extern S800D6658 func_800D6658;
