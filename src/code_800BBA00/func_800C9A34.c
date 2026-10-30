/* @header
 * func_800C9A34
 * VRAM 0x800C9A34 | ROM 0xBCED4 | size 0x8C
 * asm: asm/nonmatchings/code_800BBA00/func_800C9A34.s
 */
#include "common.h"

s32 func_800A7328(void *);
void beginEntityActionA8D8C(void *);
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
extern void *D_800FAF5C;

/* Two-state action on D_800FAF5C (state +0xC): state 0 plays animation 0xF05 and
 * advances; state 1, once the timer (+4) reaches 1, tears the action down and
 * restarts the entity action. */
void func_800C9A34(void) {
    s16 temp_v1;

    temp_v1 = *(s16 *)((u8 *)D_800FAF5C + 0xC);
    switch (temp_v1) {
    case 0:
        func_800A7328(D_800FAF5C);
        func_800D427C(D_800FAF5C, 0xF05, 2);
        *(s16 *)((u8 *)D_800FAF5C + 0xC) = (s16) ((u16) *(s16 *)((u8 *)D_800FAF5C + 0xC) + 1);
        return;
    case 1:
        if (*(s16 *)((u8 *)D_800FAF5C + 4) == temp_v1) {
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
        }
        return;
    }
}
