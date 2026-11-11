/* @header
 * func_80008C94
 * VRAM 0x80008C94 | ROM 0x9894 | size 0x54
 * asm: asm/nonmatchings/main/func_80008C94.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007BD38 and D_800485A0 */
extern u8 *D_8007BD38;
extern void *D_800485A0[];
#endif
#ifndef TARGET_PC /* on PC this label of the stream record D_800706A8 does not exist: it is read by field name */
extern u8 D_800706C4[];
#endif

u8 *allocateHeap(s32);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(void *, s32);
void func_80003684(void *, s32, s32);
#endif
void releaseHeapBlock(void *);
f32 func_8000B370(s16);
void guScaleF(void *, f32, f32, f32);

/* Set the uniform scale of part arg0's matrix from its size. */
void func_80008C94(s16 arg0) {
    f32 f = func_8000B370(arg0);

#ifdef TARGET_PC
    /* PC: the matrix is the field mtx of the stream record (Nw2AnimStream, common.h), which the N64 reaches through
     * the label D_800706C4 (+0x1C of the first record) and the record's N64 size, 0xFC. */
    guScaleF(D_800706A8[arg0].mtx, f, f, f);
#else
    guScaleF(D_800706C4 + arg0 * 0xFC, f, f, f);
#endif
}
