/* @header
 * func_8000DF78
 * VRAM 0x8000DF78 | ROM 0xEB78 | size 0x38
 * asm: asm/nonmatchings/main/func_8000DF78.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the type of func_8000335C's PC definition, which takes the handle of the sound to ask about. */
s32 func_8000335C(s32 handle);
#else
s32 func_8000335C();
#endif
s32 MusHandleStop(s32, s32);

/* When the current track is nonzero, release audio resource arg0 at level 2. */
void func_8000DF78(s32 arg0) {
#ifdef TARGET_PC
    /* PC: on the N64 a0 still holds arg0 at the call (asm: the jal is the third instruction), so func_8000335C asks
     * about this sound's handle; on PC the handle must be passed. */
    if ((func_8000335C(arg0) << 0x10) != 0) {
#else
    if ((func_8000335C() << 0x10) != 0) {
#endif
        MusHandleStop(arg0, 2);
    }
}
