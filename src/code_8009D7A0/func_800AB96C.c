#include "common.h"

extern u8 *D_800FABD0, *D_800FAF58;
extern s8 *D_800F9B60;
extern s16 D_800FAF50[];
extern s16 D_800E35D8[];
extern u8 D_800E35B4[];
extern f64 D_800E4E20;
extern f64 D_800E4E28;
s8 func_800D4198(s16);
s8 func_800AB43C(void);
void func_800AD958(s32);
void func_800ADA38(void *);

void func_800AB96C(void) {
    if ((*(u64 *)(D_800FAF58 + 0x20) & 0x40000ULL) || (!(*(u64 *)(D_800FAF58 + 0x20) & 0x80000ULL) && *(s16 *)(D_800FABD0 + 0x28) >= 0x79 && func_800D4198(((s16)(D_800FAF50[*D_800F9B60] / 3) + 1) * 40))) {
        func_800AD958(0x22); return;
    }
    if (!func_800AB43C()) {
        if (*(f32 *)(D_800FABD0 + 0x34) > D_800E4E20 && func_800D4198(*(s16 *)(D_800FABD0 + 0x12))
            && func_800D4198(D_800E35D8[(s8)*(u8 *)(*(u8 **)(D_800FAF58 + 0x364) + 0x18) / 3])) {
            func_800AD958(7); return;
        }
        if (*(s16 *)(D_800FABD0 + 0x22) == 0xD) { func_800AD958(0x27); return; }
        if (*(f32 *)(D_800FABD0 + 0x3C) > D_800E4E28) { func_800AD958(0x21); return; }
        if (*(u64 *)(D_800FAF58 + 0x20) & 0x80000ULL) goto two;
        if (!func_800D4198(*(s16 *)(D_800FABD0 + 0x12))) goto ada;
        if (func_800D4198(*(s16 *)(D_800FABD0 + 0x24) < 0x28 ? 0x2EE : 0x1F4)) {
        two:
            func_800AD958(2); return;
        }
        if (func_800D4198(500)) { func_800AD958(6); return; }
        if (func_800D4198(500)) { func_800AD958(3); return; }
        func_800AD958(1); return;
    ada:
        func_800ADA38(D_800E35B4);
    }
}
