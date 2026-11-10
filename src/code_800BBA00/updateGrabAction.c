/* @header
 * updateGrabAction  (originally func_800C61D8)
 * VRAM 0x800C61D8 | ROM 0xB9678 | size 0x240
 * asm: asm/nonmatchings/code_800BBA00/updateGrabAction.s
 */
#include "common.h"

extern s32 D_800E3F20[];
extern s32 D_800FABD8;
extern s8 D_800FADB8;
void func_800D427C(void *, s32, s32);
void func_800A7F6C(void *, s32);
void func_800A7C40(void *, s8, s16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
s8 func_800C2CDC(void *, s32);
void func_800C3A78(void *, void *, s32);
void func_800D25D0(void *, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
void func_800D2B64(void *, f32, s32, s32);
#endif
void func_800A7188(void *);

/* Three-step grab action for D_800FAF5C: step 0 plays animation 0xB4 and
 * arms it; step 1 looks for a nearby target wrestler and, when one is found,
 * advances and attaches to its record; step 2 re-aims the action,
 * applies a position/scale correction chosen by the animation id (with a
 * 4.0/2.0 scale depending on the height threshold), then updates it. */
void updateGrabAction(void)
{
    s32 id;
    s8 targetIndex;
    f32 scale;
    Wrestler *p;

    switch (D_800FAF5C->step) {
    case 0:
        func_800A7C40(D_800FAF5C, D_800FADB8, 0xB4);
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
        func_800A7F6C(D_800FAF5C, 0);
        D_800FAF5C->step = D_800FAF5C->step + 1;
    case 1:
        id = D_800FADB8;
        D_800FABD8 &= ~D_800E3F20[id];
        targetIndex = func_800C2CDC(D_800FAF5C, 1);
        if (targetIndex != -1) {
            D_800FAF5C->step = D_800FAF5C->step + 1;
            func_800C3A78(D_800FAF5C, &D_800F9D10[targetIndex], 0x100);
        }
    case 2:
        scale = 2.0f;
        func_800D25D0(D_800FAF5C, scale);
        p = D_800FAF5C;
        if ((p->flags & 0x0ULL) != 0 || (p->flags & 0x100) != 0) {
            func_800D2B64(p, scale, 0, 0xFFFFE);
        } else {
            switch ((s16)(p->state - 7)) {
            case 15:
                if (p->animFrame > p->anim.hitEnd) {
                    func_800D2B64(p, 2.0f, 0, 0xE);
                }
                break;
            case 0: case 24: case 25: case 26: case 29: case 30: case 31: case 78: case 79:
                if (p->animFrame > p->anim.hitEnd) {
                    func_800D2B64(p, 4.0f, 0, 0xFFFFE);
                } else {
                    func_800D2B64(p, 2.0f, 0, 0xE);
                }
                break;
            case 1: case 23: case 27: case 28: case 32:
                func_800D2B64(D_800FAF5C, 2.0f, 0, 0xE);
                break;
            }
        }
        func_800A7188(D_800FAF5C);
        break;
    }
}
