/* @header
 * updateActionRecordStateAEEC8  (originally func_800AEEC8)
 * VRAM 0x800AEEC8 | ROM 0xA2368 | size 0x2F0
 * asm: asm/nonmatchings/code_8009D7A0/func_800AEEC8.s
 */
#include "common.h"

/* Drives the D_800FABD0 action record through its states (s16 +4, 0..4): state 0
 * checks the facing angle between the two entities and their attachment flags to
 * pick a follow-up state; states 1/2 wait on a distance timer; state 3/4 time out
 * the close-range hold and then reset the record. */
typedef struct {
    u8 p0[2]; s16 f2; s16 state; u16 f6; u8 p8[4]; s8 fC; u8 pD; s16 timer;
    u8 p10[0x12]; s16 f22; u8 p24[0xA]; u16 f2E; u8 p30[4]; f32 f34;
    u8 p38[0x20]; s32 f58; u32 flags;
} Nw2ActAEEC8;
typedef struct {
    u8 p0[0xA]; s16 state; u8 pC[0x14]; u64 flags; u8 p28[0x30]; s32 f58; u8 p5C[0x308]; u8 *att;
} Nw2EntAEEC8;
typedef struct { u8 p0[0x38]; u64 f38; } Nw2AttAEEC8;
extern Nw2ActAEEC8 *D_800FABD0;
extern Nw2EntAEEC8 *D_800FAF58;
extern Nw2EntAEEC8 *D_800F9B60;
extern f64 D_800E51F0;
extern f64 D_800E51F8;
s8 func_800D4198(s16);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);

void updateActionRecordStateAEEC8(void) {
    Nw2ActAEEC8 *p;
    switch (D_800FABD0->state) {
    case 0:
        if (func_800D3550(func_800D3684(D_800FAF58->f58, D_800F9B60->f58)) >= 0x701) {
            if ((D_800FAF58->flags & 0x80000ULL) != 0
                && (((Nw2AttAEEC8 *)D_800FAF58->att)->f38 & 0x100000000000ULL) != 0) {
                D_800FABD0->state = 2;
            } else if (func_800D4198(0x1F4)) {
                D_800FABD0->state = 1;
            } else {
                D_800FABD0->state = 2;
            }
            return;
        }
        p = D_800FABD0;
        goto tail;
    case 1:
        p = D_800FABD0;
        if (p->f34 < D_800E51F0) {
            p->timer = 0xF;
            p->state = 3;
            return;
        }
        goto tail;
    case 2:
        p = D_800FABD0;
        if (p->f34 < D_800E51F8) {
            p->timer = 3;
            p->state = 3;
            return;
        }
        goto tail;
    tail:
        if (p->f22 != 5) {
            p->f2 = 0;
            p->state = 0;
            p->f2E = D_800F9B60->state;
            p->flags &= ~7;
        }
        return;
    case 3:
        D_800FABD0->timer--;
        if ((s16)D_800FABD0->timer > 0) {
            if ((D_800FAF58->flags & 0x80000ULL) != 0
                && (((Nw2AttAEEC8 *)D_800FAF58->att)->f38 & 0x100000000000ULL) != 0) {
                D_800FABD0->fC = (int)0x50;
            } else {
                D_800FABD0->f6 = 0x8000;
            }
        }
        if (D_800FAF58->state == 1) {
            return;
        }
        if (D_800FAF58->state == 0x44) {
            D_800FABD0->state += 1;
            return;
        }
        D_800FABD0->f2 = 0;
        D_800FABD0->state = 0;
        D_800FABD0->f2E = D_800F9B60->state;
        D_800FABD0->flags &= ~7;
        return;
    case 4:
        if (D_800FAF58->state == 0x44) {
            D_800FABD0->timer--;
            if ((s16)D_800FABD0->timer > 0) {
                D_800FABD0->f6 = 0x8000;
            }
            return;
        }
        D_800FABD0->f2 = 0;
        D_800FABD0->state = 0;
        D_800FABD0->f2E = D_800F9B60->state;
        D_800FABD0->flags &= ~7;
        return;
    }
}
