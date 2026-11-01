/* @header
 * func_800B9970
 * VRAM 0x800B9970 | ROM 0x660E0 | size 0x60
 * asm: asm/nonmatchings/code_80090000/func_800B9970.s
 */
#include "common.h"

extern s32 D_800DCFC4, D_800DCFBC;
s32 func_8000424C(void);
s32 func_800B9640(s32, s32);
void func_80004290(void);
typedef struct { u16 a; u16 b; s32 c; } X;
extern X D_800D2900[];

s32 func_800B9970(s32 i) {
    D_800DCFC4 = func_8000424C();
    D_800DCFBC = func_800B9640(D_800D2900[i].a, D_800D2900[i].b);
    func_80004290();
    return D_800DCFBC;
}
