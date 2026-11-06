/* @header
 * func_800BF2FC
 * VRAM 0x800BF2FC | ROM 0xB279C | size 0x3C
 * asm: asm/nonmatchings/code_800BBA00/func_800BF2FC.s
 */
#include "common.h"

/* Returns healthMax while SPECIAL is active, otherwise health. */
s32 func_800BF2FC(Wrestler *entity) {
    s32 value;

    if (entity->flags & WR_FLAG_SPECIAL) {
        value = entity->healthMax;
    } else {
        value = entity->health;
    }
    return value;
}


s8 func_800D26A0(void *, s32, s8);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);

void func_800D3E40(void *, void *, s32, void *);
