/* @header
 * updateActionStateDCD64  (originally func_800DCD64)
 * VRAM 0x800DCD64 | ROM 0xD0204 | size 0x258
 * asm: asm/nonmatchings/code_800BBA00/updateActionStateDCD64.s
 */
#include "common.h"

/* Action state machine for D_800FAF5C (switch on step):
 *  0 -> enter clip 0xE0 and fall through;
 *  1 -> clear the global ability mask D_800E3F20[mode]; once animFrame
 *       reaches anim.hitStart move from the apron to the floor (flag 0x80 ->
 *       0x100), then advance when func_800DB4FC reports the interaction finished;
 *  2 -> raise flag 0x80000000000, and when animFrame reaches anim.hitEnd lower
 *       it and push forward; once animFramesLeft runs out, either run the paired
 *       finish (func_800A7D1C 0x23, func_800B68A0, optional addEntityHealthDelta
 *       of move.spiritOnFinish, then beginEntityActionA8D8C) or just end with
 *       action 0x2B. */
extern s8 D_800FADB8;
extern s32 D_800E3F20[];
extern s32 D_800FABD8;
void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
void func_800D427C(void *, s32, s32);
void func_800A7F6C(void *, s32);
s8 func_800DB4FC(void *, void *);
void func_800D2B64(void *, f32, s32, s32);
void func_800D4AD0(void *);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
s8 func_800D4CC4(void *);
void addEntityHealthDelta(void *, s8);
void beginEntityActionA8D8C(void *);

void updateActionStateDCD64(void) {
    Wrestler *s;

    switch (D_800FAF5C->step) {
    case 0:
        func_800A7C40(D_800FAF5C, D_800FADB8, 0xE0);
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
        func_800A7F6C(D_800FAF5C, 0);
        D_800FAF5C->step = D_800FAF5C->step + 1;
    case 1:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        if (D_800FAF5C->animFrame >= D_800FAF5C->anim.hitStart) {
            D_800FAF5C->flags = (D_800FAF5C->flags & 0xFFFFFFFFFFFFFF7FULL) | 0x100ULL;
        }
        if (func_800DB4FC(D_800FAF5C, D_800F9B00) != 0) {
            D_800FAF5C->step = D_800FAF5C->step + 1;
        }
    case 2: {
        u64 flags = D_800FAF5C->flags | 0x80000000000ULL;
        D_800FAF5C->flags = flags;
        if (D_800FAF5C->animFrame >= D_800FAF5C->anim.hitEnd) {
            D_800FAF5C->flags = flags & 0xFFFFF7FFFFFFFFFFULL;
            func_800D2B64(D_800FAF5C, 4.0f, 0, 0xFFFFE);
        }
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            s = D_800FAF5C;
            if (s->step == 1) {
                func_800A7D1C(s, 0x23);
                func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
                if (func_800D4CC4(s) != 0) {
                    addEntityHealthDelta(s, s->move.spiritOnFinish);
                }
                beginEntityActionA8D8C(s);
            } else {
                func_800A6C48(s, 0x2B);
            }
        }
        break;
    }
    }
}
