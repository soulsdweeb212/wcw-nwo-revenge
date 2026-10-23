#include "common.h"

/* Entity thrown/knockback state machine (states 0..4). The entity E
 * (D_800FAF5C) is thrown by its partner P (D_800F9B00): it runs the throw
 * hip-check (updateEntityBoundaryFlags/func_800BF018), plays the throw animation, moves
 * along its trajectory vector (0x33C) via translateEntityXZ, then clears the
 * throw flag and slot (f362) and frees the display object. */
typedef struct {
    u8 pad0[4];
    s16 f4;             /* +0x04 animation countdown */
    u8 pad6[2];
    u16 f8;             /* +0x08 base animation id */
    s16 fA;             /* +0x0A action type */
    s16 fC;             /* +0x0C case selector */
    u8 pad10[0x10];
    u64 f20;            /* +0x20 entity status bits */
    u8 pad28[0x14];
    u16 f3C;            /* +0x3C */
    u16 f3E;            /* +0x3E facing quadrant */
    u8 pad40[0x18];
    s32 f58;            /* +0x58 heading */
    u8 pad5C[0x304];
    u16 f360;           /* +0x360 action flags */
    s8 f362;            /* +0x362 */
} Nw2BE4E0Obj;

extern void *D_800FAF5C;
extern void *D_800F9B00;
extern s8 D_800FADB8;
extern u16 D_800FAF8E[];
extern s32 D_800E3C90[];

s8 updateEntityBoundaryFlags(void *, void *, u16 *);
s16 func_800BF018(void *, void *, u16);
s8 func_800BF150(void *, void *);
void func_800D8D74(void *, void *);
s16 func_800D7A2C(u16);
void func_800D7E80(void *, s32);
void func_800D37C0(s32, f32, void *);
f32 func_800D63F0(void *, void *, s32);
void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
void func_800D427C(void *, s16, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);
void beginEntityActionA8D8C(void *);

#define E ((Nw2BE4E0Obj *)D_800FAF5C)
#define P ((Nw2BE4E0Obj *)D_800F9B00)
void updateEntityThrownState(void)
{
    Nw2BE4E0Obj *ent;
    switch (E->fC) {
    case 0:
        if (E->fA == 0xD) {
            E->f3E = P->f3C;
        } else {
            E->f3E = E->f3C;
        }
        if (updateEntityBoundaryFlags(D_800FAF5C, D_800F9B00, &D_800FAF8E[D_800FADB8]) << 24) {
            E->f360 |= 1;
        }
        {
            s16 anim = (E->fA == 0xD) ? 0x10DF : 0x10EF;
            if (E->f360 & 1) {
                anim += 8;
            }
            func_800D427C(D_800FAF5C, anim, 2);
        }
        func_800D7E80(D_800FAF5C, 0);
        E->fC++;
        return;
    case 1:
        func_800D8D74(D_800FAF5C, D_800F9B00);
        if (E->f4 > 0) {
            return;
        }
        E->f58 = func_800D35B0(E->f58, ((E->f360 & 1) ? 0 : -0x400) | 0x400);
        func_800D427C(D_800FAF5C, (s16)(E->f8 + 2), 1);
        func_800D37C0(D_800E3C90[func_800D7A2C(D_800FAF8E[D_800FADB8])], func_800D63F0(D_800FAF5C, NULL, 5), (u8 *)D_800FAF5C + 0x33C);
        E->fC++;
        return;
    case 2:
        translateEntityXZ(D_800FAF5C, (u8 *)D_800FAF5C + 0x33C);
        translateEntityXZ(D_800F9B00, (u8 *)D_800FAF5C + 0x33C);
        {
            s16 r = func_800BF018(D_800FAF5C, D_800F9B00, D_800FAF8E[D_800FADB8]);
            if (r != 0) {
                if (r == 1) {
                    E->f360 |= 2;
                } else {
                    E->f360 |= 4;
                }
            }
        }
        if (func_800BF150(D_800FAF5C, D_800F9B00) << 24) {
            E->f360 |= 4;
        }
        if (E->f360 & 2) {
            if (P->f20 & 0x2000000ULL) {
                E->f360 = (E->f360 & 0xFFFD) | 4;
            } else {
                func_800D427C(D_800FAF5C, (s16)(E->f8 + 2), 3);
                E->fC++;
                return;
            }
        }
        if (E->f360 & 4) {
            func_800D427C(D_800FAF5C, (s16)(E->f8 + 4), 3);
            E->fC += 2;
        }
        return;
    case 3:
        if (E->f4 > 0) {
            return;
        }
        func_800A7F6C(D_800FAF5C, 0x53);
        func_800A837C(D_800FAF5C);
        func_800D4AD0(D_800FAF5C);
        func_800A6C48(D_800FAF5C, 0x2B);
        break;
    case 4:
        if (E->f4 > 0) {
            return;
        }
        func_800D4AD0(D_800FAF5C);
        beginEntityActionA8D8C(D_800FAF5C);
        break;
    default:
        return;
    }
    ent = (Nw2BE4E0Obj *)D_800FAF5C;
    ent->f362 = -1;
    ent->f20 &= 0xFFFFFFFFBFFFFFFFULL;
}
#undef E
#undef P
