/* @header
 * func_80008AF0
 * VRAM 0x80008AF0 | ROM 0x96F0 | size 0x6C
 * asm: asm/nonmatchings/main/func_80008AF0.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: port_decls.h declares D_8007BD38 and D_800485A0. D_800485B0 (the stream slots' s8 [4][8] table) lies right after
 * D_800485A0's four words on the N64; the store after the loop below lands in it (see there). */
extern s8 D_800485B0[][8];
#else
extern u8 *D_8007BD38;
extern void *D_800485A0[];
#endif

void releaseHeapBlock(void *);

/* Frees the animation source and the four D_800485A0 buffers. */
void func_80008AF0(void) {
    u32 i;
#ifdef TARGET_PC
    u8 **p; /* PC: the type of D_800485A0's entries (port_decls.h) */
#else
    void **p;
#endif

    i = 0;
    p = D_800485A0;
    releaseHeapBlock(D_8007BD38);
    D_8007BD38 = NULL;
    do {
        releaseHeapBlock(*p++);
        i++;
    } while (i < 4U);
#ifdef TARGET_PC
    /* PC: i is 4 here, so the N64 stores a zero word one past D_800485A0's four entries (sw $zero at D_800485A0 +
     * 0x10), which is D_800485B0's first four bytes: entries 0 to 3 of slot 0 become 0. On PC D_800485A0's entries
     * are 8 bytes and the variables need not lie next to each other, so D_800485A0[4] would be outside both; the PC
     * clears those four bytes of D_800485B0 by name instead. */
    D_800485B0[0][0] = 0;
    D_800485B0[0][1] = 0;
    D_800485B0[0][2] = 0;
    D_800485B0[0][3] = 0;
#else
    D_800485A0[i] = NULL;
#endif
}
