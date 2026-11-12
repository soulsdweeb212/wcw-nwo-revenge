/* @header
 * func_800C2CAC
 * VRAM 0x800C2CAC | ROM 0x6F41C | size 0x30
 * asm: asm/nonmatchings/code_80090000/func_800C2CAC.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800E79B8 holds the address of a heap block of four 0x6D0-byte records (func_800C5010 allocates it), so it is
 * a pointer; an s32 would cut it in half. */
extern u8 *D_800E79B8;
#else
extern s32 D_800E79B8;
#endif

#ifdef TARGET_PC
/* PC: the same field (+0x6B6 of record arg0), reached from the pointer. */
s16 func_800C2CAC(s32 arg0) {
    return *(s16 *)(D_800E79B8 + arg0 * 0x6D0 + 0x6B6);
}
#else
s16 func_800C2CAC(s32 arg0) {
    return (*(s16 *)((u8 *)((arg0 * 0x6D0) + D_800E79B8) + 0x6B6));
}
#endif
