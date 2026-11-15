/* @header
 * func_800B0EC4
 * VRAM 0x800B0EC4 | ROM 0x5D634 | size 0x44
 * asm: asm/nonmatchings/code_80090000/func_800B0EC4.s
 */
#include "common.h"

extern u8 D_8007EF30[];
#ifdef TARGET_PC
/* PC: the type of func_8002B710's definition, which takes the id to look up. */
s32 func_8002B710(s32 id);
#else
s32 func_8002B710(void);
#endif

#ifdef TARGET_PC
/* PC: on the N64 this function does not touch a0 before it calls func_8002B710 (asm: the jal is its third
 * instruction), so func_8002B710 looks up the caller's first argument: the wrestler id that func_800AEB68,
 * func_800B0524 and func_800AC144 pass (they declare s32 func_800B0EC4(s32)). On PC an argument reaches only a
 * parameter that is declared, so the PC definition takes the id and passes it on. */
s32 func_800B0EC4(s32 id) {
    s32 v = func_8002B710(id);
    s32 r;
    if (v) {
        r = -((D_8007EF30[0x14C] >> (v - 1)) & 1);
    } else {
        r = -1;
    }
    return r;
}
#else
s32 func_800B0EC4(void) {
    s32 v = func_8002B710();
    s32 r;
    if (v) {
        r = -((D_8007EF30[0x14C] >> (v - 1)) & 1);
    } else {
        r = -1;
    }
    return r;
}
#endif
