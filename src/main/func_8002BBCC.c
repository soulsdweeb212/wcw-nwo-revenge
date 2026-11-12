/* @header
 * func_8002BBCC
 * VRAM 0x8002BBCC | ROM 0x2C7CC | size 0x70
 * asm: asm/nonmatchings/main/func_8002BBCC.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: func_8002B7E0 returns the address of a 0x2A-byte record (its definition returns Nw2Move *, a type of its own
 * file, and takes the slot as a u32). Declared to return an s32, the call would keep only the lower 32 bits of it. */
void *func_8002B7E0(s32, u32);
#else
s32 func_8002B7E0(s32, s32);
#endif
void bcopy(void *, void *, s32);

/* Copies the four 0x2A-byte name variants (0x18- and 0xA-byte halves) of the
 * group arg0 into consecutive records. */
void func_8002BBCC(s32 arg0) {
    u8 *base = (u8 *)func_8002B7E0(arg0, 0);
    s32 i;
    u8 *p;
    i = 1;
    p = base + 0x2A;
    for (; i < 4; i++) {
        bcopy(base, p, 0x18);
        bcopy(base + 0x19, p + 0x19, 0xA);
        p += 0x2A;
    }
}
