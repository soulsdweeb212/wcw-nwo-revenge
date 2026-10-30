/* @header
 * func_80090300
 * VRAM 0x80090300 | ROM 0x3CA70 | size 0x84
 * asm: asm/nonmatchings/code_80090000/func_80090300.s
 */
#include "common.h"

extern u8 applyMovementToEntityPair[];
void func_800948BC(s32);
s32 func_80090384(s32, s32, s32);

/* Resets the 0x30 movement-pair slots (marking them 0x80, clearing their
 * counters) and then runs the per-slot update 0x12C times. */
void func_80090300(void) {
    u8 *p;
    s32 i;
    s32 j;

    p = (u8 *)applyMovementToEntityPair + 0x3E;
    for (i = 0; i < 0x30; i++) {
        p[i * 0x178 - 0x14E] = p[i * 0x178 - 0x14E] | 0x80;
        *(s16 *)(p + i * 0x178 - 6) = -1;
        *(s32 *)(p + i * 0x178 + 0xE) = 0;
        *(s16 *)(p + i * 0x178 - 4) = 0;
        *(s16 *)(p + i * 0x178) = 0;
    }
    for (j = 0; j < 0x12C; j++) {
        func_800948BC(j);
        func_80090384(0, 0, 1);
    }
}

s32 func_80002C58(void);
s32 func_80002C74(void);
s32 func_8000E55C(s32, s32, s32);
s32 func_800C4D70(void);
s32 func_800C5010(void);
s32 func_800C51A0(void);
s32 func_800C594C(void);
extern s32 D_800D6D30;
