/* @header
 * func_8000337C
 * VRAM 0x8000337C | ROM 0x3F7C | size 0x44
 * asm: asm/nonmatchings/main/func_8000337C.s
 */
#include "common.h"

void func_800033C0(s32);
#ifdef TARGET_PC
/* PC: the type of MusStartSong's definition (libmus, which the port replaces with a stand-in): it takes the address
 * of the song, which an s32 would cut in half. */
s32 MusStartSong(void *);
#else
s32 MusStartSong(s32);
#endif
extern s32 D_8002EED0;

/* When arg0 is nonzero, reset the current track and load the new one; return the
 * current track id. */
#ifdef TARGET_PC
/* PC: the only caller, func_8000E55C, passes the address of the song it has just loaded (D_800487F0), and the function
 * passes it on to MusStartSong; an s32 would cut it in half, so the PC definition takes a pointer (port_decls.h
 * declares it so). */
s32 func_8000337C(void *arg0) {
    if (arg0 != NULL) {
        func_800033C0(0);
        D_8002EED0 = MusStartSong(arg0);
    }
    return D_8002EED0;
}
#else
s32 func_8000337C(s32 arg0) {
    if (arg0 != 0) {
        func_800033C0(0);
        D_8002EED0 = MusStartSong(arg0);
    }
    return D_8002EED0;
}
#endif
