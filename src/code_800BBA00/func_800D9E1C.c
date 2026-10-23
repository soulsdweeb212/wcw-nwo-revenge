#include "common.h"

void func_800A6BE0(void *, s32);
/* Pairs two entities: plays complementary animations 0x7F/0x80 (chosen by
 * arg0's 0x200 flag), raises arg0's 0x1000000000 and arg1's 0x1020000000 flags,
 * and when arg2 is set puts both into state 2. */
void func_800D9E1C(void *arg0, void *arg1, s16 arg2) {
    func_800A6BE0(arg0, (*(u64 *)((u8 *)arg0+0x20) & 0x200) ? 0x80 : 0x7F);
    *(u64 *)((u8 *)arg0+0x20) |= 0x1000000000ULL;
    func_800A6BE0(arg1, (*(u64 *)((u8 *)arg0+0x20) & 0x200) ? 0x7F : 0x80);
    *(u64 *)((u8 *)arg1+0x20) |= 0x1020000000ULL;
    if (arg2) {
        *(s16 *)((u8 *)arg0+0xC)=2;
        *(s16 *)((u8 *)arg1+0xC)=2;
    }
}
