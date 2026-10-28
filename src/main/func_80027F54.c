#include "common.h"

extern s32 D_800389A0;
extern u8 D_80064AC0[];
extern u8 D_80073E98[];
extern u8 D_80070A98;

extern s32 D_80037248;
extern void *D_80037250;

s32 func_8001C890(void *, void *, s32);
s32 func_8001C990(void *, void *, s32);
s32 func_8001CAC0(void *, s32, s32);
s32 nw2DisableInterrupts(void);
void func_800265AC(s32 *, s32);
void nw2RestoreInterrupts(s32);

/* Lazily initializes the Controller Pak message queue and then blocks for one
 * message into sp10. */
void func_80027F54(void) {
    s32 sp10;

    if (D_800389A0 == 0) {
        D_800389A0 = 1;
        func_8001C890(D_80064AC0 + 0xF3D8, D_80064AC0, 1);
        func_8001CAC0(D_80073E98, 0, 0);
    }
    func_8001C990((u8 *)&D_80070A98 + 0x3400, &sp10, 1);
}
