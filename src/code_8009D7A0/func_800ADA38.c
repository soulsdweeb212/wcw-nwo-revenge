/* @header
 * func_800ADA38
 * VRAM 0x800ADA38 | ROM 0xA0ED8 | size 0xAC
 * asm: asm/nonmatchings/code_8009D7A0/func_800ADA38.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;
s32 func_800D4148(void);

/* Select an action from the threshold table arg0 (entries of {threshold s16,
 * action u16, flags u16}, terminated by threshold -1) and apply it to the action
 * record: choose the first entry whose threshold exceeds the current level r,
 * copy its action and flags (clearing the low 3 flag bits first) and sync the
 * target's sub-state into +0x2E. */
void func_800ADA38(s16 *arg0) {
    s16 r;
    s16 *p;
    u16 a;
    u8 *o;
    u8 *g;

    p = arg0;
    r = func_800D4148();
    while (*p != -1) {
        if (*p >= r) {
            break;
        }
        p += 3;
    }
    a = *(u16 *)(p + 1);
    o = D_800FABD0;
    g = D_800F9B60;
    *(u16 *)(o + 2) = a;
    *(s16 *)(o + 4) = 0;
    *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
    *(u32 *)(o + 0x5C) &= ~7;
    *(u32 *)(o + 0x5C) |= *(u16 *)(p + 2);
}
