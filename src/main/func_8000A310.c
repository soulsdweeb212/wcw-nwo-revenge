/* @header
 * func_8000A310
 * VRAM 0x8000A310 | ROM 0xAF10 | size 0xCC
 * asm: asm/nonmatchings/main/func_8000A310.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC these labels of the stream record D_800706A8 do not exist: it is read by field name */
extern u8 D_800706B0[];
extern u8 D_800706C2[];
#endif
extern u8 D_80070C40[];
#ifndef TARGET_PC /* on PC, port_decls.h declares func_8000AA70 */
s32 func_8000AA70(void *, void *, void *);
#endif
void func_80009990(s16);

#ifdef TARGET_PC
/* PC: the stream record is Nw2AnimStream (common.h), read by field name: frame is the N64's +0x1A (D_800706C2) and
 * cursor, a u8 * here, its +0x8 (D_800706B0). As on the N64, bones 1 to 19 of the stream's wrestler are decoded at
 * the cursor, which advances by what func_8000AA70 returns. The bones (D_80070C40, 23 records of 0x7C bytes per
 * wrestler) hold only floats and keep their N64 layout, so they are reached by the N64's strides. */
void func_8000A310(s16 arg0)
{
    Nw2AnimStream *s = &D_800706A8[arg0];
    u8 *bones = D_80070C40 + arg0 * 0xB24;
    u32 i;

    if (s->frame > 0) {
        func_80009990(arg0);
    }
    for (i = 1; i < 0x14; i++) {
        s->cursor = func_8000AA70(s->cursor, (f32 *)(bones + i * 0x7C), bones + i * 0x7C + 0xC);
    }
}
#else
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
#endif
