/* @header
 * func_800AE37C
 * VRAM 0x800AE37C | ROM 0xA181C | size 0xF0
 * asm: asm/nonmatchings/code_8009D7A0/func_800AE37C.s
 */
#include "common.h"

extern u8 *D_800FABD0;
#define A(o,t) (*(t *)(D_800FABD0+(o)))
/* Two-state action handler on D_800FABD0 (state +4). State 0 sets the count
 * word to 0x8000 and advances. State 1 branches on the AI wrestler's state:
 * 0x44 keeps the count word, 1/0x2B resets the action to substate 1 with the
 * opponent's state copied to +0x2E, and anything else resets fully to substate 0. */
void func_800AE37C(void) {
    switch(A(4,s16)) {
    case 0: A(6,u16)=0x8000; A(4,s16)++; break;
    case 1:
        switch(D_800FAF58->state) {
        case 0x44: A(6,u16)=0x8000; break;
        case 1: case 0x2B: {
            u8 *p=D_800FABD0; Wrestler *g=D_800F9B60;
            *(s16 *)(p+2)=1; *(s16 *)(p+4)=0;
            A(0x2E,u16)=g->state;
            A(4,s16)=1;
            A(0x5C,u32)&=~7;
            break; }
        default: {
            Wrestler *g=D_800F9B60;
            A(2,s16)=0; A(4,s16)=0;
            A(0x2E,u16)=g->state;
            A(0x5C,u32)&=~7;
            break; }
        }
        break;
    }
}
#undef A
