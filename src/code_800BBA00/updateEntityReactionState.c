#include "common.h"

/* Entity reaction/block state machine (states 0..6). The reacting entity E
 * (D_800FAF5C) responds to its partner P's actionFlags (D_800F9B00): it plays
 * reaction animations (func_800D427C), keeps the pair aligned (func_800D2BEC /
 * func_800D2B64), and on a counter reaction flips both entities' 0x40000000
 * flag and resets their slot indices before releasing the pair. */
typedef struct {
    s8 id;              /* +0x00 */
    u8 pad1[3];
    s16 animTimer;      /* +0x04 countdown; <=0 means the animation is done */
    s16 f6;
    s16 f8;
    s16 fA;
    s16 state;          /* +0x0C case selector */
    s16 fE;
    u8 pad10[6];
    s16 f16;
    s16 f18;            /* +0x18 reaction counter */
    u8 pad1A[6];
    u64 flags;          /* +0x20 entity status bits */
    u8 pad28[0x329];
    u8 f351;            /* +0x351 slot index */
    u8 f352;            /* +0x352 */
    u8 f353;            /* +0x353 */
    u8 pad354[0xC];
    u16 actionFlags;    /* +0x360 */
    s8 f362;            /* +0x362 */
} Nw2ObjC94CC;
#define E ((Nw2ObjC94CC *)D_800FAF5C)
#define P ((Nw2ObjC94CC *)D_800F9B00)
extern void *D_800FAF5C;
extern void *D_800F9B00;
extern void *D_800F9B64;
extern u8 D_800FABE4;
extern u8 D_800FADB8;
extern s8 D_800FAF78;
extern u16 D_800FAF8A;
void func_800A6BE0(void *, s32);
void func_800A6C48(void *, s32);
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
s16 func_800B6DEC(void *, void *, s32);
void func_800C472C(void *, void *, s32);
s32 func_800D2B64(void *, f32, u16, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
s16 func_800D7690(void *, s32, s32);
s32 func_800D7894(void *, u16);

void updateEntityReactionState(void) {
    s32 animId;
    u16 partnerFlags;

    switch (E->state) {
    case 0:
        if (P->actionFlags & 8) {
            E->state = 6;
            animId = 0x10D1;
        } else {
            E->state++;
            animId = 0x10C1;
        }
        func_800D427C(E, animId, 3);
        break;
    case 1:
        if (E->animTimer <= 0) {
            func_800D427C(E, 0x10C3, 1);
            E->f18 = func_800B6DEC(E, D_800F9B00, 6);
            func_800D7690(E, 0, 0);
            E->state++;
        }
        break;
    case 2:
        E->flags |= 0x400000000000ULL;
        func_800D2BEC(E, D_800F9B00, 0, 4.0f, 0, 0xFFFFE);
        partnerFlags = P->actionFlags;
        if (partnerFlags & 1) {
            func_800D427C(E, 0x10C5, 1);
            E->state++;
            break;
        }
        if (partnerFlags & 0x10) {
            animId = (E->flags & 0x8000000) ? 0x10CF : 0x10CB;
            func_800D427C(E, animId, 1);
            E->state = 4;
            break;
        }
        if (partnerFlags & 4) {
            func_800D427C(E, 0x10C7, 1);
            E->state = 5;
            break;
        }
        if (partnerFlags & 2) {
            func_800D427C(E, func_800D5438(E, 0), 1);
            func_800A6BE0(E, 0x53);
            func_800A6BE0(D_800F9B00, 0x54);
            E->flags |= 0x40000000;
            P->flags &= ~0x40000000;
            E->f362 = D_800FABE4;
            P->f362 = -1;
            P->f351 = D_800FADB8;
            P->f353 = D_800FADB8;
            func_800A7F6C(E, 0);
            func_800A837C(E);
        } else {
            if (func_800D7894(E, D_800FAF8A) << 24) {
                if (D_800FAF78) {
                    E->f18 = 0;
                } else {
                    if (E->flags & 9) {
                        P->actionFlags |= 1;
                    } else {
                        P->actionFlags |= 2;
                        func_800A7C40(E, D_800FADB8, 0x8F);
                    }
                }
            }
        }
        break;
    case 4:
        func_800D2B64(E, 2.0f, 0, 2);
        if (E->animTimer <= 0) {
            E->f353 = E->f352;
            func_800B68A0(D_800F9B64, D_800F9B64, E);
            func_800D4AD0(E);
            beginEntityActionA8D8C(E);
            func_800C472C(D_800F9B64, E, 2);
        }
        break;
    case 3:
    case 5:
    case 6:
        func_800D2BEC(E, D_800F9B00, 0, 4.0f, 0, 0xFFFFE);
        if (E->animTimer <= 0) {
            func_800D4AD0(E);
            func_800A6C48(E, 0x2B);
        }
        break;
    }
}
#undef E
#undef P
