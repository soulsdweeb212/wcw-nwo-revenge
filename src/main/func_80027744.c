/* @header
 * func_80027744
 * VRAM 0x80027744 | ROM 0x28344 | size 0x6C
 * asm: asm/nonmatchings/main/func_80027744.s
 */
#include "common.h"

extern s32 D_800388A0;
extern s32 D_80037600;
extern s32 D_80037608;
extern u8 D_80064AB0[];
extern u8 D_8007E210[];

s32 func_8001C890(void *, void *, s32);
s32 func_8001C990(void *, void *, s32);
s32 func_8001CAC0(void *, s32, s32);

/* One-time setup: register the send/receive queues and enqueue message 0,
 * then block on the queue anchored above D_800388A0 for the next message. */
void func_80027744(void) {
    s32 sp10;

    if (D_800388A0 == 0) {
        D_800388A0 = 1;
        func_8001C890(D_80064AB0 + 0x19760, D_80064AB0, 1);
        func_8001CAC0(D_8007E210, 0, 0);
    }
    func_8001C990((u8 *)&D_800388A0 + 0x45970, &sp10, 1);
}
