/* @header
 * func_800B0518
 * VRAM 0x800B0518 | ROM 0xA39B8 | size 0x1D8
 * asm: asm/nonmatchings/code_8009D7A0/func_800B0518.s
 */
#include "common.h"

typedef struct {
    s16 f0, timer, phase, facing, f8;
    u8 padA[0x24];
    u16 savedOpponentState;
    u8 pad30[0x2C];
    u32 flags5C;
} Nw2Action0518;
extern Nw2Action0518 *D_800FABD0;
extern u16 D_800E3CF0[];
extern u8 D_8007E228[], D_8007EF30[];
s32 func_800D36E8(f32, f32);
s32 func_800D3614(s32);
s8 func_800D4198(s16);

#define REG280 (*(u16 *)(D_8007E228 + 0x58))
#define REG0A0 (*(u16 *)(D_8007EF30 + 0x170))

/* Idle/approach action controller: case 0 picks a facing from the AI
 * wrestler's x/z position and, when it is in state 0x61, advances (state 1
 * resets only past the apron/legal gates); case 1 re-faces after a 500-tick test.
 * The common exit resets the action phase and remembers the opponent state. */
void func_800B0518(void) {
    s16 state;

    switch (D_800FABD0->phase) {
    case 0:
        D_800FABD0->f8 = 8;
        D_800FABD0->facing = D_800E3CF0[(s16)func_800D3614(func_800D36E8(D_800FAF58->x, D_800FAF58->z))];
        state = D_800FAF58->state;
        if (state != 1) {
            if (state == 0x61) {
                D_800FABD0->phase++;
            } else {
                Wrestler *opp = D_800F9B60;
                u16 oldState;
                D_800FABD0->timer = 0;
                D_800FABD0->phase = 0;
                oldState = opp->state;
                D_800FABD0->flags5C &= ~7;
                D_800FABD0->savedOpponentState = oldState;
            }
        } else if (!(!(REG280 & 0x200) || (REG0A0 & 0x40) ||
                     (D_800FAF58->flags & WR_FLAG_LEGAL) ||
                     !(D_800FAF58->flags & WR_FLAG_ON_APRON))) {
            Wrestler *opp = D_800F9B60;
            u16 oldState;
            D_800FABD0->timer = 0;
            D_800FABD0->phase = 0;
            oldState = opp->state;
            D_800FABD0->flags5C &= ~7;
            D_800FABD0->savedOpponentState = oldState;
        }
        if (!(D_800FAF58->flags & 0x8000ULL)) return;
        break;
    case 1:
        if (func_800D4198(500)) D_800FABD0->facing = 8;
        if (D_800FAF58->state == 0x61) return;
        break;
    default:
        return;
    }
    {
        Wrestler *opp = D_800F9B60;
        D_800FABD0->timer = 0;
        D_800FABD0->phase = 0;
        D_800FABD0->savedOpponentState = opp->state;
        D_800FABD0->flags5C &= ~7;
    }
}
