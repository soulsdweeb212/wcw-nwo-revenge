/* @header
 * func_80007B84
 * VRAM 0x80007B84 | ROM 0x8784 | size 0x34
 * asm: asm/nonmatchings/main/func_80007B84.s
 */
#include "common.h"

/* Allocate arg1 8-byte records from the second pool in arg0. */
#ifdef TARGET_PC
/* PC: not ported yet. arg0 is an arena (D_8007C3D0[n], 16 bytes), whose second pool's base address is the 4-byte field
 * at +8: func_80007A74 stores it there, and func_8000C91C clears it. That record has no PC layout yet (docs/port.md,
 * "Shared records on PC"), and a 64-bit address cannot be read back from 4 bytes, so the PC stops the program here
 * instead of handing out records at half an address. Its PC layout must also make this pool's records sizeof(Gfx)
 * bytes, since func_8000498C builds 16-byte display-list commands in them on PC. */
void *func_80007B84(void *arg0, s32 arg1) {
    (void)arg0;
    (void)arg1;
    port_fatal("func_80007B84: the arena record (D_8007C3D0) has no PC layout yet");
}
#else
void *func_80007B84(void *arg0, s32 arg1) {
    u16 used = *(u16 *)((u8 *)arg0 + 0xE);
    s32 off = used * 8;
    u16 cap = *(u16 *)((u8 *)arg0 + 0xC);
    s32 p = *(s32 *)((u8 *)arg0 + 8);

    p += off;
    used += arg1;
    *(u16 *)((u8 *)arg0 + 0xE) = used;
    return (used <= cap) ? (void *)p : NULL;
}
#endif
