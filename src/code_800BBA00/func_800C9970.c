/* @header
 * func_800C9970
 * VRAM 0x800C9970 | ROM 0xBCE10 | size 0xC4
 * asm: asm/nonmatchings/code_800BBA00/func_800C9970.s
 */
#include "common.h"

extern s32 D_800F9B00;
extern void *D_800FAF5C;

s32 func_800A7188(void *);
void func_800D427C(void *, s32, s32);
void func_800D7E80(void *, s32);
void func_800D8D74(void *, s32);

/* Two-case action state machine for the D_800FAF5C object: state 0 plays animation 0xF04,
 * calls func_800D7E80 with the D_800F9B00 partner and advances the state (falling through
 * into case 1); state 1 drives func_800D8D74 and, once func_800A7188 reports completion,
 * resets the signed byte +0x362 to -1 and clears u64 flag 0x40000000. */
void func_800C9970(void) {
    s16 state;
    u8 *e;

    state = *(s16 *)((u8 *)D_800FAF5C + 0xC);
    switch (state) {
    case 0:
        func_800D427C(D_800FAF5C, 0xF04, 2);
        func_800D7E80(D_800FAF5C, D_800F9B00);
        *(u16 *)((u8 *)D_800FAF5C + 0xC) = *(u16 *)((u8 *)D_800FAF5C + 0xC) + 1;
        /* fallthrough */
    case 1:
        func_800D8D74(D_800FAF5C, 0);
        if (func_800A7188(D_800FAF5C) << 24) {
            e = (u8 *)D_800FAF5C;
            *(s8 *)(e + 0x362) = -1;
            *(u64 *)(e + 0x20) &= ~0x40000000;
        }
        break;
    }
}
