/* @header
 * func_80094054
 * VRAM 0x80094054 | ROM 0x407C4 | size 0x84
 * asm: asm/nonmatchings/code_80090000/func_80094054.s
 */
#include "common.h"

void releaseHeapBlock(s32);
extern u8 func_800DB4FC[];
extern u8 handleEntityState38To3F[];
extern u8 func_800DBB80[];

/* Releases the gameplay heap buffers held in the D_800DB4FC / 0x800DBBxx blocks
 * and clears the two optional pointers. */
void func_80094054(void) {
    releaseHeapBlock(*(s32 *)(func_800DB4FC + 0x19C));
    releaseHeapBlock(*(s32 *)(func_800DB4FC + 0x194));
    releaseHeapBlock(*(s32 *)(handleEntityState38To3F + 0x3C));
    if (*(s32 *)(func_800DB4FC + 0x1A0) != 0) {
        releaseHeapBlock(*(s32 *)(func_800DB4FC + 0x1A0));
        *(s32 *)(func_800DB4FC + 0x1A0) = 0;
    }
    if (*(s32 *)(func_800DB4FC + 0x1A4) != 0) {
        releaseHeapBlock(*(s32 *)(func_800DB4FC + 0x1A4));
        *(s32 *)(func_800DB4FC + 0x1A4) = 0;
    }
    *(s32 *)(func_800DBB80 + 0x1C0) = 0;
}
