/* @header
 * func_800B9DA0
 * VRAM 0x800B9DA0 | ROM 0x66510 | size 0x40
 * asm: asm/nonmatchings/code_80090000/func_800B9DA0.s
 */
#include "common.h"

typedef struct { u8 pad[0x20]; u8 n[0x30]; } R;
extern R *D_800D2970;
extern s32 D_800DCFCC;
extern u8 D_800D67B4[];
u8 *func_800B9DA0(s32 i) {
    if (i >= D_800DCFCC) {
        return D_800D67B4;
    }
    return D_800D2970[i].n;
}
