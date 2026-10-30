/* @header
 * func_8009001C
 * VRAM 0x8009001C | ROM 0x3C78C | size 0x9C
 * asm: asm/nonmatchings/code_80090000/func_8009001C.s
 */
#include "common.h"

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
extern s32 D_800D6D30;

/* Main match loop: stops the current sound, runs the per-frame update chain
 * (audio, input, scene, entity actions) and blocks until the frame handler
 * D_800D6D30 reports a result, exiting when it goes positive. */
void func_8009001C(void) {
    s32 v;

    func_8000E55C(-1, 0, 0);
    func_80002C74();
    do {
        func_800C4D70();
        func_800C5010();
        D_800D6D30 = 0;
        func_80002C74();
        if (D_800D6D30 == 0) {
            do {
                v = func_800C594C();
                D_800D6D30 = v;
            } while (v == 0);
        }
        func_80002C58();
        func_80002C74();
        func_800C51A0();
        func_80002C74();
    } while (D_800D6D30 <= 0);
}
