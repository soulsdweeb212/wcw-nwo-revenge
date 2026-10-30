/* @header
 * func_800A3EF0
 * VRAM 0x800A3EF0 | ROM 0x97390 | size 0x138
 * asm: asm/nonmatchings/code_8009D7A0/func_800A3EF0.s
 */
#include "common.h"

extern void *D_800EB414;
void func_800A9290(void *);
void func_800B68A0(void *, void *, void *);
void func_800C472C(void *, void *, s32);
s32 func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
typedef struct { s32 f0; s16 f4, f6; s32 f8; s16 fC; u8 pad[10]; s16 f18; } Action3EF0;
#define E ((Action3EF0 *)D_800EB408)
#define F(o) (*(u64 *)((u8 *)(o) + 0x20))
/* Three-state action machine on the D_800EB408 object's s16 +0xC:
 *   0: enter the action, advance to state 1
 *   1: start animation 0xFC7 when flag 0x200000 is set, else 0xFC6; hand the
 *      action off to the paired D_800EB414 object; advance to state 2
 *   2: run the boundary-correction/timer update; when the +0x4 timer expires,
 *      exit the action back to state 1, decrement the +0x18 counter by 15 and
 *      tell the paired object. */
void func_800A3EF0(void) {
    s32 animId;
    switch (E->fC) {
    case 0: func_800A9290(D_800EB408); E->fC++; break;
    case 1:
        if (F(D_800EB408) & 0x200000) animId = 0xFC7; else animId = 0xFC6;
        func_800D427C(D_800EB408, animId, 6);
        func_800B68A0(D_800EB414, D_800EB414, D_800EB408);
        E->fC++; break;
    case 2:
        func_800D2B64(D_800EB408, 4.0f, 0, 0xFFFFE);
        if (E->f4 <= 0) {
            func_800D4AD0(D_800EB408); func_800A6C48(D_800EB408, 0x2C);
            E->fC = 1; E->f18 -= 15;
            func_800C472C(D_800EB414, D_800EB408, 1);
        } break;
    }
}
