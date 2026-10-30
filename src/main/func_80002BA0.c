/* @header
 * func_80002BA0
 * VRAM 0x80002BA0 | ROM 0x37A0 | size 0x20
 * asm: asm/nonmatchings/main/func_80002BA0.s
 */
#include "common.h"

extern s32 D_800467FC;
extern s32 D_80046800;

/* Resets the two event counters and puts both objects into state 1. */
void func_80002BA0(void *arg0, void *arg1) {
    D_800467FC = 0;
    D_80046800 = 0;
    *(s16 *)((u8 *)arg0 + 0xA) = 1;
    *(s16 *)((u8 *)arg1 + 0xA) = 1;
}
