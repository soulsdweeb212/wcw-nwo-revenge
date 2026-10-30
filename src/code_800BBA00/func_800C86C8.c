/* @header
 * func_800C86C8
 * VRAM 0x800C86C8 | ROM 0xBBB68 | size 0x348
 * asm: asm/nonmatchings/code_800BBA00/func_800C86C8.s
 */
#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4, f6, f8, fA, fC, fE;
    u8 pad10[0x10];
    u64 flags;
    u8 pad28[4];
    unsigned long f2C;
    u8 pad30[0x1C];
    f32 f4C;
    u8 pad50[0x310];
    u16 f360;
    s8 f362;
} Nw2PairedActor;

#define ACTOR ((Nw2PairedActor *)D_800FAF5C)
#define PARTNER ((Nw2PairedActor *)D_800F9B00)

extern void *D_800FAF5C, *D_800F9B00;
extern f32 D_800EB540[];
extern u16 D_800FABE6, D_800FAF8A;
extern s8 D_800FADB8;

void func_800A6C48(void *, s32);
s8 func_800A93C0(void);
void applyEntityMovementC8D84(void *, void *, s32, s32);
s32 func_800D2B64(void *, f32, u16, s32);
f32 func_800D3890(void *, void *, void *);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);

/* Five-state paired-action/throw machine on ACTOR->fC (+0xC).  State 0 raises the
 * 0x1000000000 flag and starts the approach animation (0x10A5/0x10B7 chosen by
 * flag f2C bit0x10); state 1 records the gap to PARTNER (func_800D3890) into the
 * per-entity f32 table D_800EB540 and sends the next animation; state 2 runs the
 * contact test via applyEntityMovementC8D84 and, when PARTNER's state fA is 0x73 and the
 * 0x10/action flags agree, arms f360 bits and 0x10000000; state 3 sends the
 * finishing animation (0x10A9 or 0x10BB/0x10BD by f360 bit0); state 4 keeps
 * flag 0x1000000000 and ends the action with func_800A6C48(0x2B). */
void func_800C86C8(void) {
    s16 animId;

    switch (ACTOR->fC) {
    case 0:
        ACTOR->flags |= 0x1000000000ULL;
        func_800D427C(ACTOR, (ACTOR->f2C & 0x10) ? 0x10A5 : 0x10B7, 2);
        ACTOR->fC += 1;
        break;
    case 1:
        if (ACTOR->f4 <= 0) {
            D_800EB540[(s8)D_800FADB8] = func_800D3890(&ACTOR->f4C, &PARTNER->f4C, NULL);
            if (ACTOR->f2C & 0x10) {
                animId = 0x10A7;
            } else {
                animId = 0x10B9;
            }
            func_800D427C(ACTOR, animId, 0);
            ACTOR->fC += 1;
        }
        break;
    case 2:
        if (!(ACTOR->f2C & 0x10)) {
            ACTOR->flags |= 0x400200000000000ULL;
        }
        if (PARTNER->fA != 0x73) {
            Nw2PairedActor *t = ACTOR;
            t->f362 = -1;
            t->flags &= ~0x40000000ULL;
            ACTOR->fC += 1;
        } else {
            applyEntityMovementC8D84(ACTOR, PARTNER, D_800FABE6, *(s32 *)&D_800EB540[(s8)D_800FADB8]);
            if ((D_800FAF8A & 0x10) || func_800A93C0()) {
                ACTOR->f360 |= 1;
            }
            if (ACTOR->f360 & 3) {
                ACTOR->f360 |= 4;
                ACTOR->flags |= 0x10000000ULL;
                ACTOR->fC++;
            }
        }
        break;
    case 3:
        if (ACTOR->f2C & 0x10) {
            animId = 0x10A9;
        } else {
            if (PARTNER->fA == 0x73) {
                animId = (ACTOR->f360 & 1) ? 0x10BB : 0x10BD;
            } else {
                animId = 0x10BD;
            }
        }
        func_800D427C(ACTOR, animId, 0);
        ACTOR->fC += 1;
        /* fallthrough */
    case 4:
        ACTOR->flags |= 0x1000000000ULL;
        func_800D2B64(ACTOR, 2.0f, 0, 2);
        if (ACTOR->f4 <= 0) {
            register Nw2PairedActor *t = ACTOR;
            t->f362 = -1;
            t->flags &= ~0x40000000ULL;
            func_800D4AD0(ACTOR);
            func_800A6C48(ACTOR, 0x2B);
        }
        break;
    }
}
