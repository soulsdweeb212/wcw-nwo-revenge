/* @header
 * func_80008574
 * VRAM 0x80008574 | ROM 0x9174 | size 0x18
 * asm: asm/nonmatchings/main/func_80008574.s
 */
#include "common.h"

typedef struct { s16 f0; s16 f2; } S85S;
typedef struct { u16 f0; u16 f2; } S85U;
typedef struct { s16 f0; u8 pad[250]; } S85E;

extern S85S D_800669CE[];
extern S85U D_800669CC[];
extern S85E D_800706AC[];
extern s32 D_8007BD38;
extern f64 D_8003B130;

s16 func_80008574(s32 arg0) {
    return D_800669CE[(s16)arg0].f0;
}
