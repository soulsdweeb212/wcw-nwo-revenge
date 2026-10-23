#include "common.h"

/* D_800FAF5C action state machine (cases 0..2): state 0 reads the contact/knockdown
 * flags to pick a fall or spin animation and computes the per-tick heading step;
 * state 1 either waits for the reaction probe or steps the heading over 6 ticks;
 * state 2 runs a 2.0s timeout and clears the action. Case 0 falls through to 1. */
typedef struct {
    u8 pad0[4];
    s16 timer;
    u8 pad6[6];
    s16 state;
    u8 padE[8];
    u16 spinCount;
    u8 pad18[8];
    u64 flags;
    u16 f28;
    u8 pad2A[0x2E];
    s32 heading;
    u8 pad5C[0x2EC];
    s32 stepDelta;
} Nw2F5C;
extern Nw2F5C *D_800FAF5C;
void func_800D427C(void *, s32, s32);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);
void func_800D7E80(void *, s32);
s8 func_800D8D74(void *, s32);
void func_800C278C(void *, f32);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);

void updateActionStateC2368(void) {
    s32 t0;
    switch (D_800FAF5C->state) {
    case 0:
        if (D_800FAF5C->flags & 0x40) {
            if (D_800FAF5C->f28 & 0x8000) {
                func_800D7E80(D_800FAF5C, 0);
                D_800FAF5C->flags = (D_800FAF5C->flags & ~0x40ULL) | 0x80ULL;
                t0 = 0xE7E;
            } else {
                D_800FAF5C->stepDelta = func_800D3684(D_800FAF5C->stepDelta, D_800FAF5C->heading) / 6;
                t0 = 0xE7C;
                D_800FAF5C->flags = (D_800FAF5C->flags & ~0x40ULL) | 0x180ULL;
                D_800FAF5C->spinCount = 0;
            }
        } else {
            if (D_800FAF5C->f28 & 0x8000) {
                func_800D7E80(D_800FAF5C, 0);
                D_800FAF5C->flags = (D_800FAF5C->flags & ~0x100ULL) | 0x80ULL;
                t0 = 0xE81;
            } else {
                D_800FAF5C->stepDelta = func_800D3684(D_800FAF5C->stepDelta, D_800FAF5C->heading) / 6;
                t0 = 0xE7D;
                D_800FAF5C->flags = (D_800FAF5C->flags & ~0x100ULL) | 0xC0ULL;
                D_800FAF5C->spinCount = 0;
            }
        }
        func_800D427C(D_800FAF5C, t0, 3);
        D_800FAF5C->state = D_800FAF5C->state + 1;
    case 1:
        D_800FAF5C->flags |= 0x1000000000ULL;
        if (D_800FAF5C->f28 & 0x8000) {
            if (func_800D8D74(D_800FAF5C, 0)) {
                D_800FAF5C->state = D_800FAF5C->state + 1;
            }
        } else {
            D_800FAF5C->heading = func_800D35B0(D_800FAF5C->heading, D_800FAF5C->stepDelta);
            D_800FAF5C->spinCount = D_800FAF5C->spinCount + 1;
            if ((s16)D_800FAF5C->spinCount >= 6) {
                D_800FAF5C->state = D_800FAF5C->state + 1;
            }
        }
        break;
    case 2:
        func_800C278C(D_800FAF5C, 2.0f);
        if (D_800FAF5C->timer <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    }
}
