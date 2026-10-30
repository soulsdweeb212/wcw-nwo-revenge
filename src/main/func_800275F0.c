/* @header
 * func_800275F0
 * VRAM 0x800275F0 | ROM 0x281F0 | size 0x90
 * asm: asm/nonmatchings/main/func_800275F0.s
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

/* Reads a 32-bit word from the cartridge domain at devAddr (asserting on
 * misalignment or NULL data), returning -1 if the bus is busy. */
s32 func_800275F0(u32 devAddr, u32 *data) {
    if (devAddr & 3) {
        func_8001CEE0(D_8003B980, D_8003B984, 0x33);
    }
    if (data == NULL) {
        func_8001CEE0(D_8003B980, D_8003B984, 0x34);
    }
    if (func_800281F0() != 0) {
        return -1;
    }
    *data = *(volatile u32 *)(devAddr | 0xA0000000);
    return 0;
}
