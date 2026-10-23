#include "common.h"

typedef struct {
    u8 pad0[4];
    s16 f4;
    u8 pad6[6];
    s16 fC;
    u8 padE[0xA];
    s16 f18;
    u8 pad1A[6];
    u64 flags;
    u16 f28;
    u8 pad2A[0xD];
    u8 f37;
    u8 pad38[6];
    s16 f3E;
    u8 pad40[0xC];
    f32 f4C;
    s32 pad50;
    f32 f54;
    s32 f58;
} Nw2Obj8009F;

extern f32 D_800E3C70[];
extern f32 D_800E3C74[];
extern s32 D_800E3CC0[];
extern s32 D_800EB40C;
extern u8 D_800FADCF;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
extern void *D_800FAF5C;
extern void func_800A6C48(void *, s32);
extern s8 func_800A7240(void *, s32, s32, u64);
extern void func_800A7D1C(void *, s32);
extern void beginEntityActionA8D8C(void *);
extern void func_800B68A0(void *, void *, void *);
extern s16 func_800B6DEC(void *, s32, s32);
extern void func_800D25D0(void *, f32);
extern void func_800D2B64(void *, f32, s32, s32);
extern void func_800D427C(void *, s32, s32);
extern void func_800D4AD0(void *);
extern s16 func_800D7690(void *, s32, s32);
extern s8 func_800D7894(void *, u16);

#define ACTOR ((Nw2Obj8009F *)D_800EB408)

/* Six-step action state machine on ACTOR->fC (+0xC) for the D_800EB408 action
 * object.  Steps 0/2 aim the entity at the quadrant f3E (direction tables
 * D_800E3C70/D_800E3C74 plus distance D_800E3CC0) and start the action via
 * func_800A7240; step 1 marks f37 bit0 ('busy') and hands the entity to
 * func_800B68A0; step 3 waits for the proximity/range checks
 * (func_800D7894, D_800FADCF bit0x40, ACTOR flag 0x4000, D_800FAF78); steps 4/5
 * run the recovery via func_800D2B64/func_800D4AD0 and end with
 * func_800A6C48(0x2B) or beginEntityActionA8D8C.  ACTOR->f4 is the s16 timer. */
void func_8009FCBC(void)
{
    switch (ACTOR->fC) {
    case 0:
        ACTOR->f4C = D_800E3C70[ACTOR->f3E * 2];
        ACTOR->f54 = D_800E3C74[ACTOR->f3E * 2];
        func_800D427C(ACTOR, 0xEFB, 2);
        if (!func_800A7240(ACTOR, D_800E3CC0[ACTOR->f3E], 0x155, 0)) {
            return;
        }
        if (ACTOR->f28 & 0x40) {
            func_800D427C(ACTOR, 0xF00, 2);
            ACTOR->fC = 5;
            return;
        }
        func_800D427C(ACTOR, 0xEFC, 2);
        ACTOR->fC++;
        return;
    case 1:
        ACTOR->f37 |= 1;
        if (ACTOR->f4 > 0) {
            return;
        }
        func_800A7D1C(ACTOR, 0xD);
        func_800B68A0(ACTOR, (void *)D_800EB40C, ACTOR);
        ACTOR->flags |= 0x10000000ULL;
        ACTOR->fC++;
        return;
    case 2:
        ACTOR->f37 |= 1;
        ACTOR->f4C = D_800E3C70[ACTOR->f3E * 2];
        ACTOR->f54 = D_800E3C74[ACTOR->f3E * 2];
        ACTOR->f58 = D_800E3CC0[ACTOR->f3E];
        func_800D427C(ACTOR, 0xEFD, 0);
        ACTOR->f18 = func_800B6DEC(ACTOR, 0, 2);
        func_800D7690(ACTOR, 0, 0);
        ACTOR->fC++;
        return;
    case 3:
        ACTOR->f37 |= 1;
        if ((D_800FADCF & 0x40) && (ACTOR->flags & 0x4000ULL)) {
            func_800D427C(ACTOR, 0xEFF, 0);
            ACTOR->fC++;
            return;
        }
        if (!func_800D7894(ACTOR, D_800FAF8A)) {
            return;
        }
        if (D_800FAF78) {
            ACTOR->f18 = 0;
            return;
        }
        func_800D427C(ACTOR, 0xEFF, 0);
        ACTOR->fC++;
        return;
    case 4:
        ACTOR->f37 |= 1;
        func_800D2B64(ACTOR, 2.0f, 0, 2);
        if (ACTOR->f4 > 0) {
            return;
        }
        func_800D4AD0(ACTOR);
        func_800A6C48(ACTOR, 0x2B);
        return;
    case 5:
        func_800D25D0(D_800FAF5C, 4.0f);
        if (ACTOR->f4 > 0) {
            return;
        }
        func_800D4AD0(ACTOR);
        beginEntityActionA8D8C(ACTOR);
        return;
    default:
        return;
    }
}
