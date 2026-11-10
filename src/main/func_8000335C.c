/* @header
 * func_8000335C
 * VRAM 0x8000335C | ROM 0x3F5C | size 0x20
 * asm: asm/nonmatchings/main/func_8000335C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the type of MusHandleAsk's definition (libmus, which the port replaces with a stand-in): it takes the handle of
 * the sound to ask about. */
s32 MusHandleAsk(s32 key);
#else
s32 MusHandleAsk();
#endif

/* Report whether any voice with key 0 is active. */
#ifdef TARGET_PC
/* PC: on the N64 this function does not touch a0 before it calls MusHandleAsk (asm: jal MusHandleAsk is its third
 * instruction), so MusHandleAsk gets the caller's first argument: the handle of a sound, which playEntitySound passes
 * (it declares s16 func_8000335C(s32); so do func_8000DFD0, and func_8000DF78 leaves its own a0 there). MusHandleAsk
 * counts the voices playing that handle and returns 0 at once for a handle of 0. On PC an argument reaches only a
 * parameter that is declared, so the PC definition takes the handle and passes it on. */
s32 func_8000335C(s32 handle) {
    return MusHandleAsk(handle) != 0;
}
#else
s32 func_8000335C(void) {
    return MusHandleAsk() != 0;
}
#endif
