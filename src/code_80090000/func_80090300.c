#include "common.h"

extern u8 applyMovementToEntityPair[];
void func_800948BC(s32);
s32 func_80090384(s32, s32, s32);

/* Resets the 0x30 movement-pair slots (marking them 0x80, clearing their
 * counters) and then runs the per-slot update 0x12C times. */
void func_80090300(void) {
    u8 *p;
    s32 i;
    s32 j;

    p = (u8 *)applyMovementToEntityPair + 0x3E;
    for (i = 0; i < 0x30; i++) {
        p[i * 0x178 - 0x14E] = p[i * 0x178 - 0x14E] | 0x80;
        *(s16 *)(p + i * 0x178 - 6) = -1;
        *(s32 *)(p + i * 0x178 + 0xE) = 0;
        *(s16 *)(p + i * 0x178 - 4) = 0;
        *(s16 *)(p + i * 0x178) = 0;
    }
    for (j = 0; j < 0x12C; j++) {
        func_800948BC(j);
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
extern s32 D_800D6D30;

/* Main match loop: stops the current sound, runs the per-frame update chain
 * (audio, input, scene, entity actions) and blocks until the frame handler
 * D_800D6D30 reports a result, exiting when it goes positive. */
void func_8009001C(void) {
    s32 v;

    func_8000E55C(-1, 0, 0);
    func_80002C74();
    do {
        func_800C4D70();
        func_800C5010();
        D_800D6D30 = 0;
        func_80002C74();
        if (D_800D6D30 == 0) {
            do {
                v = func_800C594C();
                D_800D6D30 = v;
            } while (v == 0);
        }
        func_80002C58();
        func_80002C74();
        func_800C51A0();
        func_80002C74();
    } while (D_800D6D30 <= 0);
}
