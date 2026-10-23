#include "common.h"

extern s32 D_800388A0;
extern u8 D_80064AB0[];
extern u8 D_8007E210[];
extern s32 D_80037600;
extern s32 D_80037608;
extern s32 D_A4080000;

s32 func_8001C890(void *, void *, s32);
s32 func_8001C990(void *, void *, s32);
s32 func_8001CAC0(void *, s32, s32);

void func_80027390(s32 arg0) {
    *(vu32 *)0xA4040010 = arg0;
}

s32 func_800273A0(s32 arg0) {
    if (*(vu32 *)0xA4040010 & 1) {
        D_A4080000 = arg0;
        return 0;
    }
    return -1;
}

s32 func_80027950(void) {
    s32 v;
    v = 0;
    if (D_80037600 != 0) {
        v = D_80037608;
    }
    return v;
}

void func_80027744(void) {
    s32 sp10;

    if (D_800388A0 == 0) {
        D_800388A0 = 1;
        func_8001C890(D_8007E210, D_80064AB0, 1);
        func_8001CAC0((void *)D_8007E210, 0, 0);
    }
    func_8001C990(D_8007E210, &sp10, 1);
}
