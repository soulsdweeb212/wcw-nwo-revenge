/* @header
 * func_80007B50
 * VRAM 0x80007B50 | ROM 0x8750 | size 0x34
 * asm: asm/nonmatchings/main/func_80007B50.s
 */
#include "common.h"

/* Allocates arg1 0x10-byte records from the descriptor's first pool (+0/+4/+6),
 * returning the block or NULL when it would overflow. */
#ifdef TARGET_PC
/* PC: not ported yet. arg0 is an arena (D_8007C3D0[n], 16 bytes), whose first pool's base address is the 4-byte field
 * at +0: func_80007A74 stores it there, and func_8000C91C clears it. That record has no PC layout yet (docs/port.md,
 * "Shared records on PC"), and a 64-bit address cannot be read back from 4 bytes, so the PC stops the program here
 * instead of handing out records at half an address. */
void *func_80007B50(void *arg0, s32 arg1) {
    (void)arg0;
    (void)arg1;
    port_fatal("func_80007B50: the arena record (D_8007C3D0) has no PC layout yet");
}
#else
void *func_80007B50(void *arg0, s32 arg1) {
    u16 used = *(u16 *)((u8 *)arg0 + 6);
    s32 off = used * 0x10;
    u16 cap = *(u16 *)((u8 *)arg0 + 4);
    s32 p = *(s32 *)arg0;

    p += off;
    used += arg1;
    *(u16 *)((u8 *)arg0 + 6) = used;
    return (used <= cap) ? (void *)p : NULL;
}
#endif
