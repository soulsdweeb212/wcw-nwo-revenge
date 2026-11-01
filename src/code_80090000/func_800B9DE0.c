/* @header
 * func_800B9DE0
 * VRAM 0x800B9DE0 | ROM 0x66550 | size 0x3C
 * asm: asm/nonmatchings/code_80090000/func_800B9DE0.s
 */
#include "common.h"

typedef struct { s32 a; u8 p[0x1C]; u8 name[0x30]; } R;
extern R *D_800D2970;
extern s32 D_800DCFCC;

s32 func_800B9DE0(s32 i) {
    s32 r;
    if (i < D_800DCFCC) {
        r = D_800D2970[i].a;
    } else {
        r = 0;
    }
    return r;
}
