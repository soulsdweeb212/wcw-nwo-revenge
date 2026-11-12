/* @header
 * func_8000B46C
 * VRAM 0x8000B46C | ROM 0xC06C | size 0xE4
 * asm: asm/nonmatchings/main/func_8000B46C.s
 */
#include "common.h"

extern u16 D_80030860[];
extern u16 D_8007C318[][23];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007C438 (void *[4][23]) */
extern u16 *D_8007C438[][23];
#endif
/* Scans the 23 texture buffers of entity arg0; for each non-null buffer whose
 * count is >=17, inspects u16 elements 16..31 and reports which of the two
 * channel masks (D_80030860[1]/[2]) have matching nonzero pixels, as bits 1/2. */
#ifdef TARGET_PC
/* PC: port_decls.h declares the blocks' addresses as void *, so each block is read through a u16 pointer. A block
 * holds a palette, which stays in the N64's byte order (docs/port.md, "Byte order on PC"), so the entries this
 * function tests are read big-endian (READ_BE16), as func_8000B884 reads the same blocks. */
u16 func_8000B46C(s16 arg0) {
    u32 result=0; u32 i,j,k;
    for(i=0;i<23;i++) {
        u16 *block = D_8007C438[arg0][i];
        if (block && D_8007C318[arg0][i]>=17U) {
            for(j=1;j<3;j++) {
                for(k=16;k<32;k++) {
                    if (!(READ_BE16(&block[k]) & ~D_80030860[j])) {
                        if(READ_BE16(&block[k])>=2U) result|=1<<j;
                    }
                }
            }
        }
    }
    return result;
}
#else
u16 func_8000B46C(s16 arg0) {
    u32 result=0; u32 i,j,k;
    for(i=0;i<23;i++) {
        if (D_8007C438[arg0][i] && D_8007C318[arg0][i]>=17U) {
            for(j=1;j<3;j++) {
                for(k=16;k<32;k++) {
                    if (!(D_8007C438[arg0][i][k] & ~D_80030860[j])) {
                        if(D_8007C438[arg0][i][k]>=2U) result|=1<<j;
                    }
                }
            }
        }
    }
    return result;
}
#endif
