/* @header
 * func_800B0518
 * VRAM 0x800B0518 | ROM 0xA39B8 | size 0x1D8
 * asm: asm/nonmatchings/code_8009D7A0/func_800B0518.s
 */
#include "common.h"

typedef struct {
    s16 f0, timer, phase, facing, f8, actionState;
    u8 padC[0x14];
    u64 flags;
    u8 pad28[6];
    u16 savedOpponentState;
    u8 pad30[0x1C];
    f32 f4C, f50, f54;
    u8 pad58[4];
    u32 flags5C;
    u8 pad60[0xC];
    f32 pos[3];
} Nw2ActionEntity;
extern Nw2ActionEntity *D_800FABD0, *D_800FAF58, *D_800F9B60;
extern u16 D_800E3CF0[];
extern u8 D_8007E228[], D_8007EF30[];
s32 func_800D36E8(f32, f32);
s32 func_800D3614(s32);
s8 func_800D4198(s16);

#define REG280 (*(u16 *)(D_8007E228 + 0x58))
#define REG0A0 (*(u16 *)(D_8007EF30 + 0x170))

/* Idle/approach action controller: case 0 picks a facing from the vector
 * between the two wrestlers and leaves the action unless the opponent is
 * already in the matching state; case 1 re-faces after a 500-tick test.
 * The common exit resets the action phase and remembers the opponent state. */
void func_800B0518(void) {
    s16 state;

    switch (D_800FABD0->phase) {
    case 0:
        D_800FABD0->f8 = 8;
        D_800FABD0->facing = D_800E3CF0[(s16)func_800D3614(func_800D36E8(D_800FAF58->f4C, D_800FAF58->f54))];
        state = D_800FAF58->actionState;
        if (state != 1) {
            if (state == 0x61) {
                D_800FABD0->phase++;
            } else {
                Nw2ActionEntity *opp = D_800F9B60;
                u16 oldState;
                D_800FABD0->timer = 0;
                D_800FABD0->phase = 0;
                oldState = opp->actionState;
                D_800FABD0->flags5C &= ~7;
                D_800FABD0->savedOpponentState = oldState;
            }
        } else if (!(!(REG280 & 0x200) || (REG0A0 & 0x40) ||
                     (D_800FAF58->flags & 0x200ULL) ||
                     !(D_800FAF58->flags & 0x80ULL))) {
            Nw2ActionEntity *opp = D_800F9B60;
            u16 oldState;
            D_800FABD0->timer = 0;
            D_800FABD0->phase = 0;
            oldState = opp->actionState;
            D_800FABD0->flags5C &= ~7;
            D_800FABD0->savedOpponentState = oldState;
        }
        if (!(D_800FAF58->flags & 0x8000ULL)) return;
        break;
    case 1:
        if (func_800D4198(500)) D_800FABD0->facing = 8;
        if (D_800FAF58->actionState == 0x61) return;
        break;
    default:
        return;
    }
    {
        Nw2ActionEntity *opp = D_800F9B60;
        D_800FABD0->timer = 0;
        D_800FABD0->phase = 0;
        D_800FABD0->savedOpponentState = opp->actionState;
        D_800FABD0->flags5C &= ~7;
    }
}
