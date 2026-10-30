/* @header
 * updateEntityCounterAttackState  (originally func_800CA2FC)
 * VRAM 0x800CA2FC | ROM 0xBD79C | size 0x45C
 * asm: asm/nonmatchings/code_800BBA00/func_800CA2FC.s
 */
#include "common.h"

/* Paired-entity counter-attack state machine (states 0..3) for entity E
 * (D_800FAF5C) reacting to partner P (D_800F9B00). It selects the counter
 * animation from the actionFlags/partner status bits, aligns to the target with
 * func_800D2BAC/func_800D2BEC, and in state 3 snaps the entity's heading toward
 * the partner (func_800D3684) before playing the counter animation. */
typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4;             /* +0x04 animation countdown */
    s16 f6;
    s16 f8;             /* +0x08 base animation id */
    s16 fA;             /* +0x0A action type */
    s16 fC;             /* +0x0C case selector */
    s16 fE;
    u8 pad10[0x10];
    u64 flags;          /* +0x20 entity status bits */
    u8 pad28[0x16];
    s16 f3E;            /* +0x3E facing quadrant */
    u8 pad40[0x18];
    s32 f58;            /* +0x58 heading */
    u8 pad5C[0x304];
    u16 f360;           /* +0x360 action flags */
    s8 f362;            /* +0x362 */
    u8 f363;
    u8 pad364[0x20];
    s8 f384;            /* +0x384 */
    u8 pad385[0x22];
    u8 f3A7;            /* +0x3A7 */
    u8 pad3A8[4];
    u32 f3AC;
} Nw2ObjCA2FC;

#define E ((Nw2ObjCA2FC *)D_800FAF5C)
#define P ((Nw2ObjCA2FC *)D_800F9B00)

extern void *D_800FAF5C;
extern void *D_800F9B00;
extern u16 D_800FAF8A;

void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
void func_800D427C(void *, s16, s32);
s32 func_800D2BAC(void *, void *, f32, s32);
s8 func_800A93C0(void);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);
void func_800D36B4(void *, void *, f32 *);
void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);

void updateEntityCounterAttackState(void) {
    s16 animId;
    s32 dir;
    u32 f;
    f32 vec[4];

    switch (E->fC) {
    case 0:
        E->flags |= 0x200000000000ULL;
        if (E->fA == 0x38) {
            func_800D427C(E, E->f8 + 2, 0);
        } else {
            func_800A7C40(E, E->f384, (s16)((s8)E->f3A7 + 0xEF));
            func_800D427C(E, func_800D5438(E, 0), 1);
        }
        E->fC++;
        break;
    case 1:
        E->flags |= 0x200000000000ULL;
        func_800D2BAC(E, D_800F9B00, 4.0f, 0xFFFFE);
        if ((P->flags & 0x8000) && !(P->flags & 0x10000)) {
            E->f360 |= 8;
        }
        if (!(E->f360 & 0x1F)) {
            if ((D_800FAF8A & 0x10) || func_800A93C0()) {
                E->f360 |= 1;
                P->f360 |= 0x40;
            }
        }
        if (!(E->f4 > 0 && (E->f360 & 0x13) == 0)) {
            f = E->f360;
            if (f & 0x1F) {
                f |= 0x20;
                E->f360 = f;
                if (f & 0x10) animId = 6;
                else if (f & 0x8) animId = 4;
                else animId = 2;
                if (E->fA == 0x38) animId = animId + E->f8;
                else animId = func_800D5438(E, animId);
                func_800D427C(E, animId, 6);
                E->fC++;
            }
        }
        break;
    case 2: {
        Nw2ObjCA2FC *ent;
        func_800D2BEC(E, D_800F9B00, NULL, 2.0f, 0, 0xFFFFE);
        ent = E;
        if (ent->f4 <= 0) {
            ent->f362 = -1;
            ent->flags &= ~0x40000000ULL;
            func_800D4AD0(E);
            func_800A6C48(E, 0x2B);
        }
        break;
    }
    case 3:
        func_800D36B4((u8 *)E + 0x7C, (u8 *)D_800F9B00 + 0x7C, vec);
        translateEntityXZ(E, vec);
        if (E->f4 > 0) break;
        func_800D4AD0(E);
        if (E->f8 == 0x1BE4) E->f58 = func_800D35B0(E->f58, 0x800);
        dir = func_800D3684(P->f58, E->f58);
        if (dir < 0) E->f3E = 1;
        else E->f3E = 3;
        switch (E->f3E) {
        case 1:
            animId = 0xF7F;
            break;
        case 3:
            animId = 0xFB1;
            break;
        }
        func_800D427C(E, animId, 1);
        E->fC = 1;
        E->flags |= 0x10000000ULL;
        break;
    }
}
#undef E
#undef P
