/* @header
 * func_800AA9A0
 * VRAM 0x800AA9A0 | ROM 0x9DE40 | size 0x200
 * asm: asm/nonmatchings/code_8009D7A0/func_800AA9A0.s
 */
#include "common.h"

/* Per-frame attack decision: if the entity is not in one of three special
 * states, and either a global countdown is zero or a difficulty/round counter
 * has reached 4, validate the current action (id 9 with a progressed frame, or
 * id 1) and, when the opponent is beyond the action's max range, trigger action
 * 0x2E. Otherwise route to one of two scripted action chains chosen by the
 * countdown. */
extern u8 *D_800FABD0, *D_800FAF58;
extern s8 D_8007E8C0[], D_800FACE8;
extern u8 D_800E33DC[], D_800E3400[];
s8 func_800AB1B0(void);
s8 func_800AB2B4(void);
s8 func_800AB43C(void);
s8 func_800D4198(s16);
void func_800AD958(s32);
void func_800ADA38(void *);
#define ACTION(o, t) (*(t *)(D_800FABD0 + (o)))
#define ENTITY_FLAGS (*(u64 *)(*(u8 **)(D_800FAF58 + 0x364) + 0x38))
void func_800AA9A0(void) {
    f32 limit;
    if (func_800AB1B0() || func_800AB2B4() || func_800AB43C()) return;
    if (D_8007E8C0[0x66C] == 0 || D_800FACE8 >= 4) {
        if (ENTITY_FLAGS & 0x1800) {
            if (ACTION(0x22, s16) == 9 && ACTION(0x28, s16) >= 61 && func_800D4198(400)) {
                if (ENTITY_FLAGS & 0x800) limit = 280.0f; else limit = 490.0f;
                if (limit < ACTION(0x34, f32)) { func_800AD958(0x2E); return; }
            }
            if (ACTION(0x22, s16) == 1 && func_800D4198(200)) {
                if (ENTITY_FLAGS & 0x800) limit = 280.0f; else limit = 490.0f;
                if (limit < ACTION(0x34, f32)) { func_800AD958(0x2E); return; }
            }
        }
        func_800ADA38(D_800E33DC);
    } else func_800ADA38(D_800E3400);
}
#undef ACTION
#undef ENTITY_FLAGS
