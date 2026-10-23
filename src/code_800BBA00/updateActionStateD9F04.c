#include "common.h"

/* Action state machine for D_800FAF5C (switch on +0x0C); a per-frame update
 * (func_800D93DC) runs first.
 *  0 -> select intro clip 0x10A0/0x109F from the entity's flag word
 *       (D_800F9D30 + +0x355*0x3B0, bit 0x400000) and advance;
 *  1 -> if a contact is detected (D_800FAF8A bit 8 and +0x358 bit
 *       0x600000000000) start action 1; otherwise, once the timer +0x04
 *       expires, end with action 0x2B;
 *  2 -> choose clip 0x10A1/0x10A2 by comparing the current distance (+0x58
 *       at D_800E3CC0[+0x3E]) against 0x400 and advance;
 *  3 -> count the hit (+0x16), set flag 0x40000000000000 (and 0x1000000 when
 *       D_800FAF8A bit 0x10 is set) and, once the timer expires, play 0xF13
 *       and enter state 4. */
typedef struct { s32 f0; s16 f4, f6; s32 f8; s16 fC, fE; u8 p10[6]; u16 f16; u8 p18[8]; volatile u64 flags; u8 p28[0x16]; s16 f3E; u8 p40[0x18]; s32 f58; u8 p5C[0x2F9]; s8 f355; u8 p356[2]; u64 f358; } ObjD9F;
extern void *D_800FAF5C;
extern u16 D_800FAF8A;
extern s32 D_800E3CC0[];
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
#define P ((ObjD9F *)D_800FAF5C)

void updateActionStateD9F04(void) {
    s32 id;
    u16 count;
    func_800D93DC(D_800FAF5C);
    switch (P->fC) {
    case 0:
        id = (*(u64 *)(D_800F9D30 + P->f355 * 0x3B0) & 0x400000ULL) ? 0x10A0 : 0x109F;
        func_800D427C(D_800FAF5C, id, 2);
        P->fC++;
        break;
    case 1:
        if ((D_800FAF8A & 8) && (P->f358 & 0x600000000000ULL)) {
            func_800A6C48(D_800FAF5C, 1);
            break;
        }
        if (P->f4 <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    case 2:
        id = func_800D3550(func_800D3684(D_800E3CC0[P->f3E], P->f58)) < 0x400 ? 0x10A1 : 0x10A2;
        func_800D427C(D_800FAF5C, id, 1);
        P->fC++;
        break;
    case 3:
        count = P->f16 + 1;
        P->flags |= 0x40000000000000ULL;
        P->f16 = count;
        if (D_800FAF8A & 0x10)
            P->flags |= 0x1000000ULL;
        if (P->f4 <= 0) {
            func_800D427C(D_800FAF5C, 0xF13, 1);
            func_800A6C48(D_800FAF5C, 0xA);
            P->fC = 4;
        }
        break;
    }
}
