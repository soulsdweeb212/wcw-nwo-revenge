/* @header
 * func_80094054
 * VRAM 0x80094054 | ROM 0x407C4 | size 0x84
 * asm: asm/nonmatchings/code_80090000/func_80094054.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the N64 reaches the five heap blocks' addresses as fields of overlay 1's BSS, D_800DB4FC + 0x194, + 0x19C,
 * + 0x1A0 and + 0x1A4 and D_800DB874 + 0x3C: they are the labels D_800DB690, D_800DB698, D_800DB69C, D_800DB6A0 and
 * D_800DB8B0, which func_800936DC and func_80094AE4 declare as pointers. On PC no label lies inside another variable
 * and an address takes 8 bytes, so the PC names each by its own label; D_800DBB80 + 0x1C0 is the counter D_800DBD40.
 * releaseHeapBlock's definition takes a u8 *. */
void releaseHeapBlock(u8 *);
extern u8 *D_800DB690;
extern u8 *D_800DB698;
extern u8 *D_800DB69C;
extern u8 *D_800DB6A0;
extern u8 *D_800DB8B0;
extern s32 D_800DBD40;
#else
void releaseHeapBlock(s32);
extern u8 D_800DB4FC[];
extern u8 D_800DB874[];
extern u8 D_800DBB80[];
#endif

/* Releases the gameplay heap buffers held in the D_800DB4FC / 0x800DBBxx blocks
 * and clears the two optional pointers. */
#ifdef TARGET_PC
void func_80094054(void) {
    releaseHeapBlock(D_800DB698);
    releaseHeapBlock(D_800DB690);
    releaseHeapBlock(D_800DB8B0);
    if (D_800DB69C != 0) {
        releaseHeapBlock(D_800DB69C);
        D_800DB69C = 0;
    }
    if (D_800DB6A0 != 0) {
        releaseHeapBlock(D_800DB6A0);
        D_800DB6A0 = 0;
    }
    D_800DBD40 = 0;
}
#else
void func_80094054(void) {
    releaseHeapBlock(*(s32 *)(D_800DB4FC + 0x19C));
    releaseHeapBlock(*(s32 *)(D_800DB4FC + 0x194));
    releaseHeapBlock(*(s32 *)(D_800DB874 + 0x3C));
    if (*(s32 *)(D_800DB4FC + 0x1A0) != 0) {
        releaseHeapBlock(*(s32 *)(D_800DB4FC + 0x1A0));
        *(s32 *)(D_800DB4FC + 0x1A0) = 0;
    }
    if (*(s32 *)(D_800DB4FC + 0x1A4) != 0) {
        releaseHeapBlock(*(s32 *)(D_800DB4FC + 0x1A4));
        *(s32 *)(D_800DB4FC + 0x1A4) = 0;
    }
    *(s32 *)(D_800DBB80 + 0x1C0) = 0;
}
#endif
