#include "common.h"

/* Action state machine (2 states) driven by the shared action record D_800FABD0.
 * state 0: arm the 16-frame sub-timer (act+6) and randomise a 4-bit field (act+0xE)
 *          from func_800D4148(), then advance to state 1.
 * state 1: re-arm act+6, count act+0xE down; on expiry reset the action (act+2 = 0,
 *          act+4 = 0) and copy the current entity's animation id into act+0x2E,
 *          clearing the low 3 bits of the action flags (act+0x5C). */
s32 func_800D4148(void);
extern u8 *D_800FABD0, *D_800F9B60;
void func_800AE6B4(void)
{
    u8 *act = D_800FABD0;
    u8 *ent;
    u32 anim;
    switch (*(s16 *)(act + 4)) {
    case 0:
        *(s16 *)(act + 6) = 16;
        *(s16 *)(D_800FABD0 + 0xe) = func_800D4148() & 12;
        (*(s16 *)(D_800FABD0 + 4))++;
        break;
    case 1:
        *(s16 *)(act + 6) = 16;
        (*(s16 *)(act + 0xe))--;
        if (*(s16 *)(act + 0xe) < 0) {
            ent = D_800F9B60;
            *(s16 *)(act + 2) = 0;
            *(s16 *)(act + 4) = 0;
            anim = *(u16 *)(ent + 0xa);
            *(u32 *)(act + 0x5c) &= ~7;
            *(u16 *)(act + 0x2e) = anim;
        }
        break;
    }
}
