/* @header
 * updateEntityActionStateD1F50  (originally func_800D1F50)
 * VRAM 0x800D1F50 | ROM 0xC53F0 | size 0x290
 * asm: asm/nonmatchings/code_800BBA00/func_800D1F50.s
 */
#include "common.h"

/* Action state machine for the primary entity D_800FAF5C paired with
 * D_800F9B00 (switch on +0x0C):
 *  0 -> pair the two entities and enter the animation clip selected by
 *       flag 0x40 (0x58/0x59), then fall through;
 *  1 -> run the clip: when +0x16 reaches the per-entity duration table
 *       D_800EB620[+0], set +0x58 from D_800EB600[+0] and either jump to
 *       state 7 (flag 0x100000) or advance via func_800CDEE4; otherwise
 *       keep moving (+0x58 via +0x348, optional collision with 0x400);
 *  2 -> drive the paired interaction, and once +0x04 expires, if
 *       func_800A83DC signals completion, clear flag 0x40000000 and end. */
typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4;
    u8 pad6[6];
    s16 fC;
    u8 padE[8];
    s16 f16;
    u8 pad18[6];
    u64 flags;
    u8 pad28[4];
    u32 f2C;
    u8 pad30[0x28];
    s32 f58;
    u8 pad5C[0x2E0];
    f32 f33C[3];
    s32 f348;
    u8 pad34C[0x16];
    s8 f362;
} Nw2Entity;

extern void *D_800FAF5C;
extern void *D_800F9B00;
extern s8 D_800FADB8;
extern s32 D_800EB600[];
extern s16 D_800EB620[];

void setupEntityMoveCD990(void *, void *);
void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s16);
void func_800D427C(void *, s16, s32);
void func_800A7F6C(void *, s32);
u16 func_800CDEE4(void *, void *);
s8 func_800A83DC(void *, void *);
void func_800B68A0(void *, void *, void *);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);
void translateEntityXZ(void *, void *);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);

#define P ((Nw2Entity *)D_800FAF5C)

void updateEntityActionStateD1F50(void) {
    switch (P->fC) {
    case 0:
        setupEntityMoveCD990(D_800FAF5C, D_800F9B00);
        func_800A7C40(D_800FAF5C, D_800FADB8,
                ((P->f2C & 0x40) ? 0x59 : 0x58));
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 2);
        func_800A7F6C(D_800FAF5C, 0);
        P->fC = P->fC + 1;
    case 1: {
        s16 advanced;
        Nw2Entity *ent = D_800FAF5C;
        void *other = D_800F9B00;
        if (ent->f16 >= D_800EB620[ent->f0]) {
            ent->f58 = D_800EB600[ent->f0];
            if (ent->f2C & 0x100000) {
                ent->fC = 7;
            } else {
                ent->f16 = func_800CDEE4(ent, other);
            }
            advanced = 1;
        } else {
            translateEntityXZ(ent, ent->f33C);
            ent->f58 = func_800D35B0(ent->f58, ent->f348);
            if (ent->f2C & 0x400) {
                func_800D2BAC(ent, other, 4.0f, 0xFFFFE);
            }
            ent->f16++;
            advanced = 0;
        }
        if (advanced) {
            P->fC = P->fC + 1;
        }
        break;
    }
    case 2:
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 4.0f, 0, 0xFFFFE);
        if (P->f4 == 1) {
            func_800B68A0(D_800FAF5C, D_800FAF5C, D_800F9B00);
        }
        if (P->f4 <= 0) {
            Nw2Entity *ent;
            if (func_800A83DC(D_800FAF5C, D_800F9B00) == 0) {
                ent = P;
                ent->f362 = -1;
                ent->flags &= 0xFFFFFFFFBFFFFFFFULL;
                func_800D4AD0(D_800FAF5C);
                func_800A6C48(D_800FAF5C, 0x2B);
            }
        }
        break;
    }
}
