/* @header
 * func_800B3D5C
 * VRAM 0x800B3D5C | ROM 0xA71FC | size 0x1C8
 * asm: asm/nonmatchings/code_8009D7A0/func_800B3D5C.s
 */
#include "common.h"

/* Four-state move sequencer for the active action (D_800FABD0). State 0 checks
 * the target's flag 0x200000 and either advances to the contact state (writing
 * facing +6=2) or jumps to state 2. State 1 waits for global state 0x30.
 * State 2 handles the contact result: on 1 it sets +6=0x4000 and advances,
 * 0x2B/0x30 keep waiting, anything else resets the action. State 3 leaves the
 * action when the global state is not 0x55, jumping to the shared reset that
 * clears +2/+4, sets +0x2E from D_800F9B60+0xA and clears flags +0x5C bits
 * 0..2. */
extern void *D_800FABD0, *D_800F9B60, *D_800FAF58;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(u32 *)((u8 *)(p) + (o)))
void func_800B3D5C(void) {
    void *p = D_800FABD0;
    s16 state = H(p, 4);
    switch (state) {
    case 0:
        if (H(p, 2) == 0x36) {
            if (*(u64 *)((u8 *)D_800F9B60 + 0x20) & 0x200000ULL) { H(p, 6) = 2; H(p, 4)++; }
            else H(p, 4) = 2;
        } else {
            if (*(u64 *)((u8 *)D_800F9B60 + 0x20) & 0x200000ULL) H(p, 4) = 2;
            else { H(p, 6) = 2; H(p, 4)++; }
        }
        break;
    case 1:
        if (H(D_800FAF58, 0xA) == 0x30) H(p, 4) = state + 1;
        else goto reset;
        break;
    case 2:
        switch (H(D_800FAF58, 0xA)) {
        case 1: H(p, 6) = 0x4000; H(p, 4)++; break;
        case 0x2B: case 0x30: break;
        default: { void *q = D_800FABD0; void *g = D_800F9B60; u16 st; H(q, 2) = 0; H(q, 4) = 0; st = U(g, 0xA); U(q, 0x2E) = st; W(q, 0x5C) &= ~7; break; }
        }
        break;
    case 3:
        if (H(D_800FAF58, 0xA) != 0x55) {
        reset:;
            { void *g = D_800F9B60; u16 st; H(p, 2) = 0; H(p, 4) = 0; st = U(g, 0xA); W(p, 0x5C) &= ~7; U(p, 0x2E) = st; }
        }
        break;
    }
}
#undef H
#undef U
#undef W
