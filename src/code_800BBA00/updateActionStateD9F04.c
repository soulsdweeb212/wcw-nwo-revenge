/* @header
 * updateActionStateD9F04  (originally func_800D9F04)
 * VRAM 0x800D9F04 | ROM 0xCD3A4 | size 0x254
 * asm: asm/nonmatchings/code_800BBA00/updateActionStateD9F04.s
 */
#include "common.h"

/* Action state machine for D_800FAF5C (switch on step); a per-frame update
 * (func_800D93DC) runs first.
 *  0 -> select intro clip 0x10A0/0x109F from the partner's flags
 *       (D_800F9D10[partnerId], bit 0x400000) and advance;
 *  1 -> if a contact is detected (D_800FAF8A bit 8 and partnerFlags bit
 *       0x600000000000) start action 1; otherwise, once animFramesLeft
 *       expires, end with action 0x2B;
 *  2 -> choose clip 0x10A1/0x10A2 by comparing heading against
 *       D_800E3CC0[dirIndex] (within 0x400) and advance;
 *  3 -> count stateTimer, set flag 0x40000000000000 (and 0x1000000 when
 *       D_800FAF8A bit 0x10 is set) and, once the animation ends, play 0xF13
 *       and enter step 4. */
extern u16 D_800FAF8A;
extern s32 D_800E3CC0[];
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);

void updateActionStateD9F04(void) {
    s32 id;
    u16 count;
    func_800D93DC(D_800FAF5C);
    switch (D_800FAF5C->step) {
    case 0:
        id = (D_800F9D10[D_800FAF5C->partnerId].flags & 0x400000ULL) ? 0x10A0 : 0x109F;
        func_800D427C(D_800FAF5C, id, 2);
        D_800FAF5C->step++;
        break;
    case 1:
        if ((D_800FAF8A & 8) && (D_800FAF5C->partnerFlags & 0x600000000000ULL)) {
            func_800A6C48(D_800FAF5C, 1);
            break;
        }
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    case 2:
        id = func_800D3550(func_800D3684(D_800E3CC0[D_800FAF5C->dirIndex], D_800FAF5C->heading)) < 0x400 ? 0x10A1 : 0x10A2;
        func_800D427C(D_800FAF5C, id, 1);
        D_800FAF5C->step++;
        break;
    case 3:
        count = D_800FAF5C->stateTimer + 1;
        D_800FAF5C->flags |= 0x40000000000000ULL;
        D_800FAF5C->stateTimer = count;
        if (D_800FAF8A & 0x10)
            D_800FAF5C->flags |= 0x1000000ULL;
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D427C(D_800FAF5C, 0xF13, 1);
            func_800A6C48(D_800FAF5C, 0xA);
            D_800FAF5C->step = 4;
        }
        break;
    }
}
