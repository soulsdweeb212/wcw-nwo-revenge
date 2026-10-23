#include "common.h"

extern u8 D_800484F0;
extern u8 D_800484F3;
extern u16 D_80048310[];
extern u8 D_800482F0[];
extern u8 D_80048350[];
s32 readWriteControllerPakBank(void *, void *, s16);
void func_800043CC(s16);

/* Save pak bank arg0: clear its dirty bit in D_800484F3, and if the bank is
 * present and allowed to save, write it to the pak. On success, if the bank
 * wasn't already saved, run func_800043CC and mark it saved. */
void func_800042BC(s16 arg0) {
    u8 saved;
    u32 bit;

    saved = D_800484F3;
    bit = 1 << arg0;
    D_800484F3 = saved & ~bit;
    if (((s32)D_800484F0 >> arg0) & 1) {
        if (D_80048310[arg0 * 2] & 4) {
            if (readWriteControllerPakBank(D_800482F0, D_80048350 + arg0 * 0x68, arg0) == 0) {
                if (!(((s32)saved >> arg0) & 1)) {
                    func_800043CC(arg0);
                }
                D_800484F3 |= bit;
            }
        }
    }
}
