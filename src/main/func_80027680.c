/* @header
 * func_80027680
 * VRAM 0x80027680 | ROM 0x28280 | size 0x6C
 * asm: asm/nonmatchings/main/func_80027680.s
 */
#include "common.h"

extern s32 D_800388A0;
extern char D_80064AB0[];
extern char D_8007E210[];
extern char D_8003B980[];
extern char D_8003B984[];
extern char D_8003B990[];
extern char D_8003B994[];
extern char D_8003B9A4[];
extern char D_8003B9A8[];
extern u32 D_80000308;

extern void func_8001C890(void *, void *, s32);
extern void func_8001C990(void *, void *, s32);
extern void func_8001CAC0(void *, s32, s32);
extern void func_8001CEE0(char *, char *, s32);
extern s32 func_800281F0(void);

/* Writes a 32-bit word to the cartridge domain at devAddr (asserting on
 * misalignment), returning -1 if the bus is busy. */
s32 func_80027680(u32 devAddr, u32 data) {
    if (devAddr & 3) {
        func_8001CEE0(D_8003B990, D_8003B994, 0x34);
    }
    if (func_800281F0() != 0) {
        return -1;
    }
    *(volatile u32 *)(devAddr | 0xA0000000) = data;
    return 0;
}
