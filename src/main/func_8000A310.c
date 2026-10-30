/* @header
 * func_8000A310
 * VRAM 0x8000A310 | ROM 0xAF10 | size 0xCC
 * asm: asm/nonmatchings/main/func_8000A310.s
 */
#include "common.h"

extern u8 D_800706B0[];
extern u8 D_800706C2[];
extern u8 D_80070C40[];
s32 func_8000AA70(void *, void *, void *);
void func_80009990(s16);

void func_8000A310(s16 arg0)
{
    s32 off;
    u32 i;
    s32 base;
    s32 j;

    off = arg0 * 0xFC;
    if (*(s16 *)(D_800706C2 + off) > 0) {
        func_80009990(arg0);
    }
    i = 1;
    base = arg0 * 0xB24;
    j = 0x7C;
loop:
    *(s32 *)(D_800706B0 + off) = func_8000AA70((void *)*(s32 *)(D_800706B0 + off),
        D_80070C40 + base + j, D_80070C40 + base + j + 0xC);
    j += 0x7C;
    i++;
    if (i < 0x14) {
        goto loop;
    }
}
