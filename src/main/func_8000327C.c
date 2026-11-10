/* @header
 * func_8000327C
 * VRAM 0x8000327C | ROM 0x3E7C | size 0x28
 * asm: asm/nonmatchings/main/func_8000327C.s
 */
#include "common.h"

s32 MusBankStartEffect(s32, s16);
extern s32 D_800482D4;

/* Forward arg0 to MusBankStartEffect with the current context D_800482D4. */
#ifdef TARGET_PC
/* PC: the callers use a result (playEntitySound and func_8000E724 declare s32 func_8000327C(s32)): the sound's
 * handle, which MusBankStartEffect leaves in v0 on the N64, where this function, declared void, does not touch v0
 * before it returns. On PC the function returns it (port_decls.h declares it so). */
s32 func_8000327C(s16 arg0) {
    return MusBankStartEffect(D_800482D4, arg0);
}
#else
void func_8000327C(s16 arg0) {
    MusBankStartEffect(D_800482D4, arg0);
}
#endif
