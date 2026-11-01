/* @header
 * func_800B88E0
 * VRAM 0x800B88E0 | ROM 0x65050 | size 0xB4
 * asm: asm/nonmatchings/code_80090000/func_800B88E0.s
 */
#include "common.h"

typedef struct { u8 b[4]; } S;
extern S D_800D67B0;
extern u8 D_800DCF50[], D_800D2960[];
extern s32 D_800DCFBC;
s32 func_8000424C(void);
void func_80004290(void);
s32 osPfsAllocateFile(void *, s32, s32, void *, void *, s32, s32 *);

void func_800B88E0(void) {
    S n = D_800D67B0;
    s32 x;
    s32 i;
    func_8000424C();
    for (i = 0; i < 0x10; i++) {
        n.b[0] = i + 0x1A;
        D_800DCFBC = osPfsAllocateFile(D_800DCF50, 0x4538, 0x4E56504A, D_800D2960, &n, 0x6B00, &x);
    }
    func_80004290();
}
