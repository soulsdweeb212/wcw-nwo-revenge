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

/* Lazily initializes the controller/Pak message queue and then blocks for one
 * message into sp10. */
void func_80027744(void) {
    u32 sp10;

    if (D_800388A0 == 0) {
        D_800388A0 = 1;
        func_8001C890(D_8007E210, D_80064AB0, 1);
        func_8001CAC0(D_8007E210, 0, 0);
    }
    func_8001C990(D_8007E210, &sp10, 1);
}

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
