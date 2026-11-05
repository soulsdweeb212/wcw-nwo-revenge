/* @header
 * main  (originally func_80000450)
 * VRAM 0x80000450 | ROM 0x1050 | size 0x68
 * asm: asm/nonmatchings/main/main.s
 */
#include "common.h"

s32 osCreateThread(s32 *, s32, void *, s32, s32 *, s32);
s32 osStartThread(s32 *);
void osInitialize(void);
extern s32 D_8003BAD0;
extern s32 D_8003DC80;
extern void func_800004B8(void);

/* Entry point: initializes the PI and RDRAM, creates the main game thread
 * (priority 1, stack at D_8003DC80, 8 KB) and starts it. */
void main(s32 arg0) {
    osInitialize();
    osCreateThread(&D_8003BAD0, 1, func_800004B8, arg0, &D_8003DC80, 8);
    osStartThread(&D_8003BAD0);
}
