/* @header
 * func_800A167C
 * VRAM 0x800A167C | ROM 0x4DDEC | size 0x64
 * asm: asm/nonmatchings/code_80090000/func_800A167C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: allocateHeap returns a pointer (its definition is void *allocateHeap(u32)), and D_800DC730, D_800DC734 and
 * D_800DC740 hold the addresses of the blocks, which an s32 would cut in half (func_8009F9A0, func_800A171C and
 * func_800A16E0 read them as pointers). */
void *allocateHeap(u32);
s32 func_800A1590();                                  /* extern */
extern void *D_800DC730;
extern void *D_800DC734;
extern s32 D_800DC73C;
extern void *D_800DC740;
#else
s32 allocateHeap(s32);                                /* extern */
s32 func_800A1590();                                  /* extern */
extern s32 D_800DC730;
extern s32 D_800DC734;
extern s32 D_800DC73C;
extern s32 D_800DC740;
#endif
extern f32 D_800DC828;

void func_800A167C(void) {
    D_800DC73C = 0;
    D_800DC828 = 1.0f;
#ifdef TARGET_PC
    /* PC: D_800DC734 is the menus' display-list buffer, two halves of 0x1000 commands (func_800A171C), and a command
     * is 16 bytes on PC (port.h's Gfx), so the block holds the N64's 0x2000 commands at sizeof(Gfx) each. */
    D_800DC734 = allocateHeap(0x2000 * sizeof(Gfx));
#else
    D_800DC734 = allocateHeap(0x10000);
#endif
    D_800DC740 = allocateHeap(0x4000);
#ifdef TARGET_PC
    /* PC: D_800DC730 holds the menus' 0x100 elements (common.h's Nw2MenuEl), 0x148 bytes each on the N64 and
     * sizeof(Nw2MenuEl) on PC, where their addresses are 8 bytes. */
    D_800DC730 = allocateHeap(NW2_MENU_EL_COUNT * sizeof(Nw2MenuEl));
#else
    D_800DC730 = allocateHeap(0x14800);
#endif
    func_800A1590();
}
