#include "common.h"

typedef struct { u16 f360; s8 f362; u8 f363; } Nw2H360;
typedef union { Nw2H360 h; u32 w; } Nw2U360;

typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[0x10];
    u64 flags;
    u8 pad28[0x338];
    Nw2U360 u360;
    u8 pad364[0x20];
    s8 f384;
    u8 pad385[0x22];
    u8 f3A7;
    u8 pad3A8[4];
    u32 f3AC;
} Nw2ObjCBE28;

#define ACTOR ((Nw2ObjCBE28 *)D_800FAF5C)

extern void *D_800FAF5C;
extern void *D_800F9B00;
extern s8 D_800FAF78;
extern u16 D_800FAF8A;

void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
void func_800D427C(void *, s16, s32);
s32 func_800D2BAC(void *, void *, f32, s32);
s8 func_800A93C0(void);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D4AD0(void *);
s16 func_800BF2FC(void *);
void addEntityHealthDelta(void *, s32);
void beginEntityActionA8D8C(void *);
void func_800A6C48(void *, s32);

/* Three-state grapple state machine on the D_800FAF5C actor's fC.  State 0
 * raises flag 0x200000000000 and sends the attack animation (0xEF + f3A7) via
 * func_800A7C40/func_800D5438/func_800D427C.  State 1 keeps that flag, toggles the
 * 0x100 'clear' bit in the u360 bitfield from D_800FAF78, applies the 4.0f
 * separation (func_800D2BAC) unless f3AC has 0x400000, arms the 0x1 'hit' bit from
 * D_800FAF8A bit0x10 or func_800A93C0, and when the timer f4 expires (or u360 bits
 * are 0x100000) selects the follow-up animation from the f360 bits (0x10 -> 6,
 * 0x208 -> 4, else 2) and advances.  State 2 runs the 2.0f separation
 * (func_800D2BEC), clears f362/flag 0x40000000, ends the action via
 * func_800BF2FC/addEntityHealthDelta, and finishes with beginEntityActionA8D8C or
 * func_800A6C48(0x2B) by f3AC bit2. */
void func_800CBE28(void) {
    s16 animId;
    s32 mode;
    u32 f;

    switch (ACTOR->fC) {
    case 0:
        ACTOR->flags |= 0x200000000000ULL;
        func_800A7C40(ACTOR, ACTOR->f384, (s16)((s8)ACTOR->f3A7 + 0xEF));
        animId = func_800D5438(ACTOR, 0);
        mode = 1;
        func_800D427C(ACTOR, animId, mode);
        ACTOR->fC++;
        break;
    case 1:
        ACTOR->flags |= 0x200000000000ULL;
        if (D_800FAF78) {
            ACTOR->u360.h.f360 |= 0x100;
        } else {
            ACTOR->u360.h.f360 &= 0xFEFF;
        }
        if (!(ACTOR->f3AC & 0x400000)) {
            func_800D2BAC(ACTOR, D_800F9B00, 4.0f, 0xFFFFE);
        }
        if (!(ACTOR->u360.h.f360 & 0x21F)) {
            if ((D_800FAF8A & 0x10) || func_800A93C0()) {
                ACTOR->u360.h.f360 |= 1;
            }
        }
        if (ACTOR->u360.h.f360 & 8) {
            ACTOR->u360.h.f360 &= 0xFFEF;
        }
        if (ACTOR->f4 <= 0 || (ACTOR->u360.w & 0x180000) == 0x100000) {
            f = ACTOR->u360.h.f360;
            if (f & 0x21F) {
                f |= 0x20;
                ACTOR->u360.h.f360 = f;
                if (f & 0x10) {
                    animId = 6;
                } else if (f & 0x208) {
                    animId = 4;
                } else {
                    animId = 2;
                }
                if (ACTOR->fA == 0x38) {
                    animId = animId + ACTOR->f8;
                } else {
                    animId = func_800D5438(ACTOR, animId);
                }
                mode = 0;
                func_800D427C(ACTOR, animId, mode);
                ACTOR->fC++;
            }
        }
        break;
    case 2: {
        Nw2ObjCBE28 *t;
        func_800D2BEC(ACTOR, D_800F9B00, NULL, 2.0f, 0, 0xFFFFE);
        t = ACTOR;
        if (t->f4 <= 0) {
            t->u360.h.f362 = -1;
            t->flags &= ~0x40000000ULL;
            func_800D4AD0(ACTOR);
            if (func_800BF2FC(ACTOR) < 0x31) {
                addEntityHealthDelta(ACTOR, 3);
            }
            if (ACTOR->f3AC & 2) {
                beginEntityActionA8D8C(ACTOR);
            } else {
                func_800A6C48(ACTOR, 0x2B);
            }
        }
        break;
    }
    default:
        break;
    }
}
