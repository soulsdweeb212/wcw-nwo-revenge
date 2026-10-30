/* @header
 * func_800AD98C
 * VRAM 0x800AD98C | ROM 0xA0E2C | size 0x5C
 * asm: asm/nonmatchings/code_8009D7A0/func_800AD98C.s
 */
#include "common.h"

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    u8 pad[0x28];
    u16 f2E;
    u8 pad2[0x2C];
    u32 f5C;
} NwObj;

extern NwObj *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;

/* Switch the action record to command arg0: reset its substate and timer, copy the
 * entity's +0xA state into +0x2E, clear the low action-flag bits and set the source
 * entity's action-locked bit. */
void func_800AD98C(s16 command) {
    NwObj *o = D_800FABD0;
    u8 *g = D_800F9B60;
    o->f2 = command;
    o->f4 = 0;
    o->f2E = *(u16 *)(g + 0xA);
    o->f5C &= ~7;
    *(u64 *)(D_800FAF58 + 0x20) |= 0x10000000;
}
