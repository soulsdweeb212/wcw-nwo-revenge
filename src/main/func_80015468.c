/* @header
 * func_80015468
 * VRAM 0x80015468 | ROM 0x16068 | size 0x24
 * asm: asm/nonmatchings/main/func_80015468.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x58];
    u64 f58;
    u8 pad60[0x50];
    u64 fB0;
    u8 padB8[0x25];
    u8 fDD;
    u8 padDE[0x1B];
    u8 fF9;
    u8 fFA;
} Nw15468Obj;

/* Snapshots the object's saved time into its shadow copy and latches the +0xDD
 * bit 0x40 into +0xFA. */
void func_80015468(Nw15468Obj *p) {
    u64 v = p->f58;
    u8 c = p->fDD;

    p->fF9 = 0;
    p->fB0 = v;
    p->fFA = c & 0x40;
}
