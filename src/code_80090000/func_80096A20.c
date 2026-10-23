#include "common.h"

extern u8 updateActionStateC5D48[];

void func_80091244(u32 **arg0) {
    u32 *p = *arg0;
    p[0] = 0xDE000000;
    p[1] = (u32)updateActionStateC5D48 + 0x48;
    *arg0 = p + 2;
}

extern u8 applyMovementToEntityPair[];
void func_800948BC(s32);
s32 func_80090384(s32, s32, s32);

void func_80090300(void) {
    u8 *p;
    s32 i;

    p = (u8 *)applyMovementToEntityPair + 0x3E;
    for (i = 0; i < 0x30; i++) {
        p[-0x14E] = p[-0x14E] | 0x80;
        *(s16 *)(p - 6) = -1;
        *(s32 *)(p + 0xE) = 0;
        *(s16 *)(p - 4) = 0;
        *(s16 *)p = 0;
        p += 0x178;
    }
    for (i = 0; i < 0x12C; i++) {
        func_800948BC(i);
        func_80090384(0, 0, 1);
    }
}

s32 func_80002C58(void);
s32 func_80002C74(void);
s32 func_8000E55C(s32, s32, s32);
s32 func_800C4D70(void);
s32 func_800C5010(void);
s32 func_800C51A0(void);
s32 func_800C594C(void);
extern u8 func_800D6658[];

void func_8009001C(void) {
    s32 v;

    func_8000E55C(-1, 0, 0);
    func_80002C74();
    do {
        func_800C4D70();
        func_800C5010();
        *(s32 *)(func_800D6658 + 0x6D8) = 0;
        func_80002C74();
        if (*(s32 *)(func_800D6658 + 0x6D8) == 0) {
            do {
                v = func_800C594C();
                *(s32 *)(func_800D6658 + 0x6D8) = v;
            } while (v == 0);
        }
        func_80002C58();
        func_80002C74();
        func_800C51A0();
        func_80002C74();
    } while (*(s32 *)(func_800D6658 + 0x6D8) <= 0);
}

extern s16 D_800E6B78;
extern s16 D_800E821C;

/* Set the two global s16 options from the arguments, ignoring a negative
 * argument (leaving the existing value in place). */
void func_80096A20(s32 a, s32 b) {
    if (a >= 0) {
        D_800E821C = a;
    }
    if (b >= 0) {
        D_800E6B78 = b;
    }
}
