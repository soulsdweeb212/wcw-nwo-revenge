/* @header
 * func_800277E0
 * VRAM 0x800277E0 | ROM 0x283E0 | size 0x94
 * asm: asm/nonmatchings/main/func_800277E0.s
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

/* Waits for the cartridge domain bus and reads the 32-bit word at devAddr into
 * *data (asserting when data is NULL). */
s32 func_800277E0(u32 devAddr, u32 *data) {
    u32 stat;

    if (data == NULL) {
        func_8001CEE0(D_8003B9A4, D_8003B9A8, 0x3D);
    }
    stat = *(volatile u32 *)0xA4600010;
    while (stat & 3) {
        stat = *(volatile u32 *)0xA4600010;
    }
    *data = *(volatile u32 *)(D_80000308 | devAddr | 0xA0000000);
    return 0;
}
