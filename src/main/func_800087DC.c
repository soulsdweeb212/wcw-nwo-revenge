/* @header
 * func_800087DC
 * VRAM 0x800087DC | ROM 0x93DC | size 0x34
 * asm: asm/nonmatchings/main/func_800087DC.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007BD38 and D_800485A0 */
extern u8 *D_8007BD38;
extern void *D_800485A0[];
#endif
extern u8 D_800706C4[];

u8 *allocateHeap(s32);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(void *, s32);
void func_80003684(void *, s32, s32);
#endif
void releaseHeapBlock(void *);
f32 func_8000B370(s16);
void guScaleF(void *, f32, f32, f32);

/* Return a pointer to record arg0 (stride 0x24) in the table at D_8007BD38. */
u8 *func_800087DC(s32 arg0) {
    u32 off = (s16)arg0 * 0x24 + 0xFFFDFFFC;
#ifdef TARGET_PC
    /* PC: off is (arg0 - 0xE39) * 0x24 in 32 bits; added as an s32 it is the same offset from the table as the N64's
     * 32-bit address sum: the same record for a valid id, and the same distance before the table (not the same
     * bytes) for an id below 0xE39 (see func_800085E4). */
    return D_8007BD38 + (s32)off + 0x14;
#else
    return D_8007BD38 + off + 0x14;
#endif
}
