/* @header
 * func_8000327C
 * VRAM 0x8000327C | ROM 0x3E7C | size 0x28
 * asm: asm/nonmatchings/main/func_8000327C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800482D4 holds the address of the sound-effect bank (port_decls.h declares it a pointer; on PC nothing sets
 * it until audio is ported, so it stays 0), and MusBankStartEffect (libmus, which the port replaces with a stand-in)
 * takes it as a pointer and the sound as an s32; an s32 would cut the address in half. */
s32 MusBankStartEffect(void *, s32);
#else
s32 MusBankStartEffect(s32, s16);
extern s32 D_800482D4;
#endif

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
