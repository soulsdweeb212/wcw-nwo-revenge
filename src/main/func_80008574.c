/* @header
 * func_80008574
 * VRAM 0x80008574 | ROM 0x9174 | size 0x18
 * asm: asm/nonmatchings/main/func_80008574.s
 */
#include "common.h"

typedef struct { s16 f0; s16 f2; } S85S;
typedef struct { u16 f0; u16 f2; } S85U;
typedef struct { s16 f0; u8 pad[250]; } S85E;

#ifdef TARGET_PC
/* PC: D_800669CE and D_800669CC are not variables: they lie 0xE39 records before the 4-byte per-animation records at
 * D_8006A2B0, whose +2 halfword (D_8006A2B2) is the animation's frame count, so that an animation id indexes them
 * directly. On the N64 that address falls inside another table, and the PC has no symbol there. So this file reads
 * D_8006A2B2 by the id minus 0xE39, with func_8000946C's view of it. D_800706AC, a label of the stream record
 * D_800706A8, does not exist on PC either (this file does not use it). */
typedef struct {
    s16 a;
    s16 b;
} A2B2Rec;
extern A2B2Rec D_8006A2B2[];
#else
extern S85S D_800669CE[];
extern S85U D_800669CC[];
extern S85E D_800706AC[];
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007BD38 */
extern s32 D_8007BD38;
#endif
extern f64 D_8003B130;

s16 func_80008574(s32 arg0) {
#ifdef TARGET_PC
    /* PC: the same s16 as the N64's D_800669CE[id].f0 (see the declarations above). */
    return D_8006A2B2[(s16)arg0 - 0xE39].a;
#else
    return D_800669CE[(s16)arg0].f0;
#endif
}
