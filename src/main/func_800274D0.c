/* @header
 * func_800274D0
 * VRAM 0x800274D0 | ROM 0x280D0 | size 0x104
 * asm: asm/nonmatchings/main/func_800274D0.s
 */
#include "common.h"

extern u8 D_80038830[];
extern s32 *__osViCurr;
extern s32 *__osViNext;
extern s16 D_80038862;
extern s16 D_80038832;
extern s32 D_80038864;
extern s32 D_80038834;
extern void *D_80038868;
extern u8 D_800388B0[];
extern u8 D_80038900[];
extern u8 D_80038950[];
extern s32 D_80000300;

typedef struct {
    s16 f0;
    s16 f2;
    s32 f4;
    s32 *f8;
    s32 fC;
} Nw2B38860;

void func_80021F60(void *, s32);
void __osViSwapContext(void);

void func_800274D0(void) {
    func_80021F60(D_80038830, 0x60);
    __osViCurr = (s32 *)D_80038830;
    __osViNext = (s32 *)&D_80038830[0x30];
    D_80038862 = 1;
    D_80038832 = 1;
    D_80038864 = 0x80000000;
    D_80038834 = 0x80000000;
    if (D_80000300 == 0)
        D_80038868 = D_80038900;
    else if (D_80000300 == 2)
        D_80038868 = D_80038950;
    else
        D_80038868 = D_800388B0;
    ((Nw2B38860 *)__osViNext)->f0 = 0x20;
    ((Nw2B38860 *)__osViNext)->fC = ((Nw2B38860 *)__osViNext)->f8[1];
    while (*(vu32 *)0xA4400010 >= 0xB) {
    }
    *(vu32 *)0xA4400000 = 0;
    __osViSwapContext();
}
