/* @header
 * func_8000858C
 * VRAM 0x8000858C | ROM 0x918C | size 0x3C
 * asm: asm/nonmatchings/main/func_8000858C.s
 */
#include "common.h"

typedef struct { u16 f0; u16 f2; } S85U;
typedef struct { s16 f0; u8 pad[250]; } S85E;

extern S85U D_800669CC[];
extern S85E D_800706AC[];
extern u8 *D_8007BD38;
extern f64 D_8003B130;

/* Decode entity arg0's 10-bit field into a scaled float. */
f32 func_8000858C(s32 arg0) {
    return (f32)((f64)(f32)(D_800669CC[(s16)arg0].f0 & 0x3FF) * D_8003B130);
}
