/* @header
 * func_800B9E34
 * VRAM 0x800B9E34 | ROM 0x665A4 | size 0x98
 * asm: asm/nonmatchings/code_80090000/func_800B9E34.s
 */
#include "common.h"

typedef struct { s32 a; s32 b; u16 c; u8 d[4]; u8 e[0x42]; } R;
extern R *D_800D2970;
extern s32 D_800DCFC4, D_800DCFBC, D_800DCFCC;
extern u8 D_800DCF50[];
s32 func_8000424C(void);
void func_80004290(void);
s32 osPfsDeleteFile(void *, s32, s32, u8 *, u8 *);

s32 func_800B9E34(s32 i) {
    D_800DCFC4 = func_8000424C();
    if (i < 0) {
        return -1;
    }
    if (i < D_800DCFCC) {
        D_800DCFBC = osPfsDeleteFile(D_800DCF50, D_800D2970[i].c, D_800D2970[i].b, D_800D2970[i].e, D_800D2970[i].d);
        func_80004290();
        return D_800DCFBC;
    }
    return -1;
}
