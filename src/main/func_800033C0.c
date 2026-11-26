/* @header
 * func_800033C0
 * VRAM 0x800033C0 | ROM 0x3FC0 | size 0x38
 * asm: asm/nonmatchings/main/func_800033C0.s
 */
#include "common.h"

typedef s32 M2C_UNK;
#ifdef TARGET_PC
/* PC: the parameter and return types of the definitions (docs/port.md, "Prototypes on PC"): the port's MusHandleStop
 * reads the fade speed as 32 bits, and on 64-bit Windows a 16-bit argument would leave the upper half unset. */
M2C_UNK MusHandleStop(s32, s32);
#else
M2C_UNK MusHandleStop(s32, s16);
#endif
extern s32 D_8002EED0;

/* Applies arg0 to the pending sound handle and clears it. */
void func_800033C0(s16 arg0) {
    if (D_8002EED0 != 0) {
        MusHandleStop(D_8002EED0, arg0);
        D_8002EED0 = 0;
    }
}
