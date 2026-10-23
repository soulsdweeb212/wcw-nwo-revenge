#include "common.h"

s8 func_800D4198(s16);
void func_800AD958(s32);
extern f64 D_800E4E78;
extern s16 D_800FAF84;
extern s16 D_800FAF50[];
extern u8 *D_800F9B60;
extern u8 *D_800FABD0;
extern u8 *D_800FAF58;

s32 func_800AC0B4(void) {
    s16 a3, a2;
    if (*(s16 *)(D_800FABD0 + 0x24) < 0x28) {
        if (*(s16 *)(D_800FABD0 + 0x28) < 0x5B) {
            if (func_800D4198((s16)(D_800FAF84 * 100)) == 0) {
                if (D_800FAF50[*(s8 *)D_800F9B60] < 0xF) {
                    return 0;
                }
            }
        }
        a3 = D_800FAF50[*(s8 *)D_800F9B60] * 40 + D_800FAF84 * 20;
        a2 = a3;
        if (*(u64 *)(D_800FAF58 + 0x20) & 0x4000000000000000ULL) {
            a2 = (s16)(s32)((f64)a3 * D_800E4E78);
        }
        if (func_800D4198(a2)) {
            func_800AD958(5);
            return 1;
        }
    }
    return 0;
}
