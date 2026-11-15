/* @header
 * func_800B9970
 * VRAM 0x800B9970 | ROM 0x660E0 | size 0x60
 * asm: asm/nonmatchings/code_80090000/func_800B9970.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800DCFC4 holds the address of the controllers' message queue that func_8000424C returns (its definition
 * returns an s32 *), which an s32 would cut in half. */
extern s32 *D_800DCFC4;
extern s32 D_800DCFBC;
s32 *func_8000424C(void);
#else
extern s32 D_800DCFC4, D_800DCFBC;
s32 func_8000424C(void);
#endif
s32 func_800B9640(s32, s32);
void func_80004290(void);
#ifdef TARGET_PC
/* PC: +4 is a u16 (the block's length), as the other files read it; the PC turns each value of the table into its
 * byte order at the width the files read it at, so the views must agree. */
typedef struct { u16 a; u16 b; u16 c; u16 d; } X;
#else
typedef struct { u16 a; u16 b; s32 c; } X;
#endif
extern X D_800D2900[];

s32 func_800B9970(s32 i) {
    D_800DCFC4 = func_8000424C();
    D_800DCFBC = func_800B9640(D_800D2900[i].a, D_800D2900[i].b);
    func_80004290();
    return D_800DCFBC;
}
