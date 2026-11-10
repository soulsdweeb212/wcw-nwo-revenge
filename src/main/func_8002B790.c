/* @header
 * func_8002B790
 * VRAM 0x8002B790 | ROM 0x2C390 | size 0x50
 * asm: asm/nonmatchings/main/func_8002B790.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_8003A594 holds the address of the buffer of 0x2A-byte name records (func_8002B750 allocates it, and
 * func_8002BAB8 declares it u8 *), which an s32 would cut in half. */
extern u8 *D_8003A594;
#else
extern s32 D_8003A594;
#endif

/* Return the pointer to the 0x2A-byte variant arg1 of group arg0 (1..0x4F), or the
 * buffer base for an out-of-range request. */
#ifdef TARGET_PC
/* PC: the result is an address in that buffer, which the callers use as a pointer (func_8002AD34 adds 0x19 to it
 * for func_80097EF4, which declares the result u8 *); an s32 would cut it in half, so the PC definition returns a
 * u8 * (port_decls.h declares it so). */
u8 *func_8002B790(s32 arg0, u32 arg1) {
#else
s32 func_8002B790(s32 arg0, u32 arg1) {
#endif
    u32 idx;

    if ((u32)(arg0 - 1) < 0x4F) {
        if (arg1 < 4) {
            goto good;
        }
    }
    return D_8003A594;
good:
    idx = arg0 * 4 + arg1;
    return D_8003A594 + idx * 0x2A;
}
