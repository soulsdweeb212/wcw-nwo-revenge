/* @header
 * main  (originally func_80000450)
 * VRAM 0x80000450 | ROM 0x1050 | size 0x68
 * asm: asm/nonmatchings/main/main.s
 */
#include "common.h"

s32 func_8001C8C0(s32 *, s32, void *, s32, s32 *, s32);
s32 startThread(s32 *);
void initializePiAndRdram(void);
extern s32 D_8003BAD0;
extern s32 D_8003DC80;
extern void func_800004B8(void);

/* Entry point: initializes the PI and RDRAM, creates the main game thread
 * (priority 1, stack at D_8003DC80, 8 KB) and starts it. */
void main(s32 arg0) {
    initializePiAndRdram();
    func_8001C8C0(&D_8003BAD0, 1, func_800004B8, arg0, &D_8003DC80, 8);
    startThread(&D_8003BAD0);
}
