#include "common.h"

void func_80017A30(s32, s32);
void func_80017AC0(s32);
extern s32 D_800604CC;

/* Resets the audio voice's link: if it was already linked, sends command 15,
 * then sends command 14 with the voice's +8 value and clears that value. */
void func_80014D78(void *arg0, s32 arg1) {
    if (*(u8 *)((u8 *)arg0 + 0xE9) != 0) {
        func_80017AC0(D_800604CC + (arg1 * 0x1C));
    }
    *(u8 *)((u8 *)arg0 + 0xE9) = 1U;
    func_80017A30(D_800604CC + (arg1 * 0x1C), *(s32 *)((u8 *)arg0 + 8));
    *(s32 *)((u8 *)arg0 + 8) = 0;
}
