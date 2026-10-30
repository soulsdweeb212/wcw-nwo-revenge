/* @header
 * func_800A9348
 * VRAM 0x800A9348 | ROM 0x9C7E8 | size 0x78
 * asm: asm/nonmatchings/code_8009D7A0/func_800A9348.s
 */
#include "common.h"

extern s16 D_800E3270[];
extern s16 D_800E3262[];
extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern u8 D_80064AD8[];

s32 func_800D35B0(s32, s32);
void func_800D4AD0(void *);
s32 func_800D4CC4(void *);
void func_800D427C(void *, s16, s32);

/* Returns 0 only when the global 0x400 gates and the entity's 0x200 flag are
 * all set and its 0x100 flag is clear. */
s32 func_800A9348(void *arg0) {
    u64 f;

    if (!(*(u16 *)(D_8007E228 + 0x58) & 0x400)) {
        return 1;
    }
    if (!(*(u16 *)(D_8007EF30 + 0x170) & 0x400)) {
        return 1;
    }
    f = *(u64 *)((u8 *)arg0 + 0x20);
    if (!(f & 0x200)) {
        return 1;
    }
    if (f & 0x100) {
        return 0;
    }
    return 1;
}
