#include "common.h"

extern u8 updateActionStateC5D48[];

/* Emits a display-list pointer to updateActionStateC5D48+0x48 into the command
 * buffer and advances the cursor. */
void func_80091244(u32 **arg0) {
    u32 *p = *arg0;
    u32 *start = p;
    p += 2;
    start[0] = 0xDE000000;
    start[1] = (u32)updateActionStateC5D48 + 0x48;
    *arg0 = p;
}

extern u8 applyMovementToEntityPair[];
void func_800948BC(s32);
s32 func_80090384(s32, s32, s32);

/* Resets the 0x30 movement-pair slots (marking them 0x80, clearing their
 * counters) and then runs the per-slot update 0x12C times. */
void func_80090300(void) {
    u8 *p;
    s32 i;
    s32 j;

    i = 0;
    p = (u8 *)applyMovementToEntityPair + 0x3E;
    for (; i < 0x30; i++) {
        p[-0x14E] = p[-0x14E] | 0x80;
        *(s16 *)(p - 6) = -1;
        *(s32 *)(p + 0xE) = 0;
        *(s16 *)(p - 4) = 0;
        *(s16 *)p = 0;
        p += 0x178;
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

typedef struct {
    u8 pad[0x6D8];
    volatile s32 flag;
} S800D6658;
extern S800D6658 func_800D6658;

/* Main match loop: stops the current sound, runs the per-frame update chain
 * (audio, input, scene, entity actions) and blocks until the frame handler
 * func_800D6658.flag reports a result, exiting when it goes positive. */
void func_8009001C(void) {
    s32 v;

    func_8000E55C(-1, 0, 0);
    func_80002C74();
    do {
        func_800C4D70();
        func_800C5010();
        func_800D6658.flag = 0;
        func_80002C74();
        if (func_800D6658.flag == 0) {
            do {
                v = func_800C594C();
                func_800D6658.flag = v;
            } while (v == 0);
        }
        func_80002C58();
        func_80002C74();
        func_800C51A0();
        func_80002C74();
    } while (func_800D6658.flag <= 0);
}
