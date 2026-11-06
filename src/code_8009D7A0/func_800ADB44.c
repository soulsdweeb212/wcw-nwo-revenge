/* @header
 * func_800ADB44
 * VRAM 0x800ADB44 | ROM 0xA0FE4 | size 0x308
 * asm: asm/nonmatchings/code_8009D7A0/func_800ADB44.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x16];
    s16 f16;
    s16 f18;
    s16 f1A;
    u8 pad1C[8];
    s16 f24;
    s16 f26;
    s16 f28;
    u8 pad2A[10];
    f32 f34;
    u8 pad38[4];
    f32 f3C;
    u8 pad40[0x1C];
    u32 f5C;
} Nw2AdbAction;

extern Nw2AdbAction *D_800FABD0;
f32 func_800ADE4C(f32, f32);

/* Prepares the D_800FABD0 action record parameters for the pair: computes scaled
 * ratios (func_800ADE4C) from the two wrestlers' health/spirit/escapeTimer and the
 * record's f3C into the record's f16/f24/f18/f26/f1A/f28/f34, clears the f5C flag
 * field 0x1FF0000, and sets a single relationship code into f5C from the zones
 * (in ring 0x40 / apron 0x80 / floor) of D_800FAF58 and D_800F9B60. */
void func_800ADB44(void) {
    register u32 bits;
    register f32 k;
    D_800FABD0->f16 = (s16)func_800ADE4C((f32)D_800FAF58->health, 0.1f);
    D_800FABD0->f24 = (s16)func_800ADE4C((f32)D_800F9B60->health, 0.3f);
    D_800FABD0->f18 = (s16)(s32)func_800ADE4C((f32)D_800FAF58->spirit, 0.1f);
    k = 0.2f;
    D_800FABD0->f26 = (s16)func_800ADE4C((f32)D_800F9B60->spirit, k);
    D_800FABD0->f1A = (s16)func_800ADE4C((f32)D_800FAF58->escapeTimer, 0.3f);
    D_800FABD0->f28 = (s16)func_800ADE4C((f32)D_800F9B60->escapeTimer, 0.3f);
    D_800FABD0->f34 = func_800ADE4C(D_800FABD0->f3C, k);
    D_800FABD0->f5C &= 0xFE00FFFF;
    if (D_800FAF58->flags & WR_FLAG_IN_RING) {
        if (D_800F9B60->flags & WR_FLAG_IN_RING) bits = 0x10000;
        else if (D_800F9B60->flags & WR_FLAG_ON_APRON) bits = 0x20000;
        else bits = 0x40000;
    } else if (D_800FAF58->flags & WR_FLAG_ON_APRON) {
        if (D_800F9B60->flags & WR_FLAG_IN_RING) bits = 0x80000;
        else if (D_800F9B60->flags & WR_FLAG_ON_APRON) bits = 0x100000;
        else bits = 0x200000;
    } else {
        if (D_800F9B60->flags & WR_FLAG_IN_RING) bits = 0x400000;
        else if (D_800F9B60->flags & WR_FLAG_ON_APRON) bits = 0x800000;
        else bits = 0x1000000;
    }
    D_800FABD0->f5C |= bits;
}
