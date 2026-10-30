/* @header
 * func_800D8D74
 * VRAM 0x800D8D74 | ROM 0xCC214 | size 0x7C
 * asm: asm/nonmatchings/code_800BBA00/func_800D8D74.s
 */
#include "common.h"

s16 func_800D7690(void *, s32, s32);
s32 func_800D35B0(s32, s32);
void translateEntityXZ(void *, void *);

extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern u8 D_800F9850[];

/* Advances the entity along its stored vector for the remaining +0x16 ticks,
 * turning by +0x348; returns 1 when the counter is exhausted. */
s32 func_800D8D74(u8 *arg0, void *arg1) {
    u16 v;

    if (*(s16 *)(arg0 + 0x16) > 0) {
        translateEntityXZ(arg0, arg0 + 0x33C);
        if (arg1 != 0) {
            translateEntityXZ(arg1, arg0 + 0x33C);
        }
        *(s32 *)(arg0 + 0x58) = func_800D35B0(*(s32 *)(arg0 + 0x58), *(s32 *)(arg0 + 0x348));
    }
    v = *(u16 *)(arg0 + 0x16) - 1;
    *(u16 *)(arg0 + 0x16) = v;
    return (v << 16) < 1;
}
