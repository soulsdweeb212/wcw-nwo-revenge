/* @header
 * func_800B36A8
 * VRAM 0x800B36A8 | ROM 0xA6B48 | size 0x150
 * asm: asm/nonmatchings/code_8009D7A0/func_800B36A8.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern f64 D_800E5398;
#define A(o,t) (*(t *)(D_800FABD0+(o)))
void func_800B36A8(void) {
    switch(A(4,s16)) {
    case 0: A(6,s16)=4; A(4,s16)++; break;
    case 1:
        switch(D_800FAF58->state) {
        case 3: if (D_800FAF58->step==2 && (f64)A(0x34,f32)<D_800E5398) { A(6,s16)=0x4000; A(4,s16)++; } break;
        case 4: A(4,s16)++; break;
        default: goto reset;
        } break;
    case 2:
        switch (D_800FAF58->state) {
        case 3: A(8,s16)=0xF00; break;
        case 4: case 6: case 7: case 0x26: break;
        default: { Wrestler *g;
            reset: g=D_800F9B60;
            A(2,s16)=0; A(4,s16)=0; A(0x2E,u16)=g->state; A(0x5C,u32)&=~7;
        } break; } break;
    }
}
#undef A
